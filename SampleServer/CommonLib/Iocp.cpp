#pragma once
#include "Iocp.h"
#include "Session.h"
#include "Logger.h"
#include "PoolManager.h"
#include <WS2tcpip.h>
#include <thread>
#include "Tr.h"
#include "TrAuth.h"
#include "SystemManager.h"
#include "NetworkContents.h"

#pragma optimize ("" , off )

Iocp::Iocp(const int threadCount)
{
	_handle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, threadCount);
	_threadCount = threadCount;
}

Iocp::~Iocp()
{
	CloseHandle(_handle);
}

void Iocp::execute()
{
	DWORD		io_byte{};
	ULONGLONG	id{}; //x64

	IocpEvents readEvents;
	getEvent(readEvents, 0);

	Actor* mainActor = SystemManager::getInstance()->getMainActor();
	NetworkContents* networkContents = static_cast<NetworkContents*>(mainActor->getContents(ContentsType::eNetwork));

	for (int index = 0; index < readEvents.m_eventCount; ++index)
	{
		OVERLAPPED_ENTRY& readEvent = readEvents.m_events[index];
		OverlappedBuffer* overlappedBuffer = reinterpret_cast<OverlappedBuffer*>(readEvent.lpOverlapped);

		Session* onEventSession = _sessionList[overlappedBuffer->_sessionKey.get()];

		if (nullptr == onEventSession)
		{
			PoolManager::getInstance()->getOverlappedBufferPool().push(overlappedBuffer);
			continue;
		}

		switch (overlappedBuffer->_type)
		{
		case BufferType::ACCEPT:
		{
			PSOCKADDR pRemoteSocketAddr = nullptr;
			PSOCKADDR pLocalSocketAddr = nullptr;
			INT pRemoteSocketAddrLength = 0;
			INT pLocalSocketAddrLength = 0;

			GetAcceptExSockaddrs(
				&overlappedBuffer->_buffer, 0,
				sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16,
				&pLocalSocketAddr, &pLocalSocketAddrLength, &pRemoteSocketAddr, &pRemoteSocketAddrLength);

			std::string connectStr = "Accept New Clients ID: " + std::to_string(overlappedBuffer->_sessionKey.get());
			Logger::getInstance()->log(Logger::Level::DEBUG, connectStr);

			recv(onEventSession);
			accept();

			onAccept(onEventSession);
		}
		break;
		case BufferType::SEND:
		{

		}
		break;
		case BufferType::RECV:
		{
			if (0 == readEvent.dwNumberOfBytesTransferred)
			{
				disconnect(onEventSession);
			}
			else
			{
				Tr* tr = new Tr();
				memcpy(tr, overlappedBuffer->_buffer, readEvent.dwNumberOfBytesTransferred);
				networkContents->recvTrEvent(tr, 0);
				
				recv(onEventSession);
			}
		}
		break;
		case BufferType::DISCONNECT:
		{
			onDisconnect(onEventSession);
		}
		break;
		case BufferType::CONNECT:
		{
			recv(onEventSession);
			onConnect();
		}
		break;
		}

		PoolManager::getInstance()->getOverlappedBufferPool().push(overlappedBuffer);
	}
}

const bool Iocp::listen(Session* session)
{
	if (SOCKET_ERROR == ::listen(session->getSocketHandle(), SOMAXCONN) )
	{
		Logger::getInstance()->log(Logger::Level::WARNING, "Error_listen");
		return false;
	}

	return true;
}

const bool Iocp::bind(Session* session, sockaddr_in& socketAddr)
{
	if (SOCKET_ERROR == ::bind(session->getSocketHandle(), reinterpret_cast<sockaddr*>(&socketAddr), sizeof(socketAddr))) 
	{
		Logger::getInstance()->log(Logger::Level::WARNING, "Error_Bind");
		return false;
	}
	return true;
}

const bool Iocp::connect(Session* session, sockaddr_in& socketAddr, TrNetworkConnectReq* tr)
{
	LPFN_CONNECTEX connectFunc;

	DWORD dwbyte{ 0 };
	GUID guid = WSAID_CONNECTEX;
	OverlappedBuffer* overlappedBuffer = PoolManager::getInstance()->getOverlappedBufferPool().pop();

	SOCKET& connectSocket = session->getSocketHandle();

	overlappedBuffer->_sessionKey = session->getSessionKey();
	overlappedBuffer->_type = BufferType::CONNECT;
	overlappedBuffer->_wsaBuffer.len = tr->_maxSize;

	memcpy(overlappedBuffer->_buffer, tr, tr->_maxSize);

	WSAIoctl(connectSocket, SIO_GET_EXTENSION_FUNCTION_POINTER,
		&guid, sizeof(guid),
		&connectFunc, sizeof(connectFunc),
		&dwbyte, NULL, NULL);

	if (FALSE == connectFunc(connectSocket, reinterpret_cast<SOCKADDR*>(&socketAddr),
							 sizeof(socketAddr), overlappedBuffer->_buffer, tr->_maxSize, NULL,
							 reinterpret_cast<LPOVERLAPPED>(&overlappedBuffer->_overlapped)) 
		) 
	{
		auto error = GetLastError();
		if (WSA_IO_PENDING != error )
		{
			Logger::getInstance()->log(Logger::Level::WARNING, "Error_Connect");
			return false;
		}
	}

	return true;
}

const bool Iocp::accept()
{
	OverlappedBuffer* overlappedBuffer = PoolManager::getInstance()->getOverlappedBufferPool().pop();
	Session* newSession = PoolManager::getInstance()->getSessionPool().pop();
	addSession(newSession);

	overlappedBuffer->_sessionKey = newSession->getSessionKey();
	overlappedBuffer->_type = BufferType::ACCEPT;

	LPFN_ACCEPTEX acceptFunc = nullptr;

	DWORD dwbyte{ 0 };
	GUID GuidAccept = WSAID_ACCEPTEX;
	WSAIoctl(_mainSession->getSocketHandle(), SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidAccept, sizeof(GuidAccept),
		&acceptFunc, sizeof(acceptFunc),
		&dwbyte, NULL, NULL);


	acceptFunc(_mainSession->getSocketHandle(), newSession->getSocketHandle(), &overlappedBuffer->_buffer, sizeof(TrNetworkConnectReq)
		, sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, &dwbyte, reinterpret_cast<LPOVERLAPPED>(&overlappedBuffer->_overlapped));

	return true;
}

const bool Iocp::disconnect(Session* session)
{
	OverlappedBuffer* overlappedBuffer = PoolManager::getInstance()->getOverlappedBufferPool().pop();

	DWORD dwbyte{ 0 };
	GUID guid = WSAID_DISCONNECTEX;

	LPFN_DISCONNECTEX disconnectFunc;
	WSAIoctl(session->getSocketHandle(), SIO_GET_EXTENSION_FUNCTION_POINTER,
		&guid, sizeof(guid),
		&disconnectFunc, sizeof(disconnectFunc),
		&dwbyte, NULL, NULL);

	overlappedBuffer->_sessionKey = session->getSessionKey();
	overlappedBuffer->_type = BufferType::DISCONNECT;

	int error = disconnectFunc(session->getSocketHandle(), reinterpret_cast<LPOVERLAPPED>(&overlappedBuffer->_overlapped), TF_REUSE_SOCKET, 0);
	if (FALSE == error)
	{
		if (WSA_IO_PENDING != GetLastError())
		{
			Logger::getInstance()->log(Logger::Level::WARNING, "Disconnect Error");
			return false;
		}
	}

	return true;
}

void Iocp::recv(Session* session)
{
	OverlappedBuffer* overlappedBuffer = PoolManager::getInstance()->getOverlappedBufferPool().pop();

	DWORD flag{ 0 };

	overlappedBuffer->_sessionKey = session->getSessionKey();
	overlappedBuffer->_type = BufferType::RECV;

	int error = WSARecv(session->getSocketHandle(), &overlappedBuffer->_wsaBuffer, 1, NULL, &flag, &overlappedBuffer->_overlapped, 0);

	if (SOCKET_ERROR == error )
	{
		if (WSA_IO_PENDING != GetLastError() )
		{
			Logger::getInstance()->log(Logger::Level::WARNING, "Error");
		}
	}
}

void Iocp::send(Session* session, Tr* tr)
{
	OverlappedBuffer* overlappedBuffer = PoolManager::getInstance()->getOverlappedBufferPool().pop();

	overlappedBuffer->_sessionKey = session->getSessionKey();
	overlappedBuffer->_type = BufferType::SEND;
	overlappedBuffer->_wsaBuffer.len = tr->_maxSize;

	memcpy(overlappedBuffer->_buffer, tr, tr->_maxSize);

	WSASend(session->getSocketHandle(), &overlappedBuffer->_wsaBuffer, 1, 0, 0, &overlappedBuffer->_overlapped, NULL);
}

void Iocp::send(Tr* tr)
{
	send(_mainSession, tr);
}

void Iocp::send(const SessionKey sessionKey, Tr* tr)
{
	auto iter = _sessionList.find(sessionKey.get());
	if (_sessionList.end() == iter)
	{
		// 에러
		return;
	}

	Session* session = iter->second;
	send(session, tr);
}

void Iocp::send(const std::vector<SessionKey> sessionKeyList, Tr* tr)
{
	const int size = sessionKeyList.size();

	for (int index = 0; index < size; ++index)
	{
		send(sessionKeyList[index], tr);
	}
}

void Iocp::addSession(Session* session)
{
	const bool result = CreateIoCompletionPort((HANDLE)session->getSocketHandle(), _handle, session->getSessionKey().get(), _threadCount);

	if (false == result)
	{
		DWORD error = GetLastError();

		Logger::getInstance()->log(Logger::Level::WARNING, "IOCP add failed!");
	}

	_sessionList.insert(std::make_pair(session->getSessionKey().get(), session));
}

void Iocp::deleteSession(const SessionKey& sessionKey)
{
	auto iter = _sessionList.find(sessionKey.get());
	if (iter == _sessionList.end())
	{
		// 에러ㅓㅓㅓㅓ 나 로그ㅡㅡㅡㅡ
		return;
	}

	Session* session = iter->second;
	
	_sessionList.erase(iter);
	PoolManager::getInstance()->getSessionPool().push(session);
}

void Iocp::getEvent(IocpEvents& output, int timeoutMs)
{
	const bool result = GetQueuedCompletionStatusEx(_handle, output.m_events, Iocp::MAX_EVENT_COUNT, (ULONG*)&output.m_eventCount, timeoutMs, FALSE);
	if (false == result)
	{
		output.m_eventCount = 0;
	}
}

const SessionKey& Iocp::getMainSessionKey()
{
	return _mainSession->getSessionKey();
}

void Iocp::onConnect()
{
}

void Iocp::onAccept(Session* acceptSession)
{
}

void Iocp::onDisconnect(Session* acceptSession)
{
}