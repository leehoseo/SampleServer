#pragma once
#include "Iocp.h"
#include "Session.h"
#include "Logger.h"
#include "PoolManager.h"
#include <WS2tcpip.h>
#include <thread>

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

void Iocp::run()
{
	runXXX();

	workerThread();
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

const bool Iocp::connect(Session* session, sockaddr_in& socketAddr)
{
	LPFN_CONNECTEX connectFunc;

	DWORD dwbyte{ 0 };
	GUID guid = WSAID_CONNECTEX;
	OverlappedBuffer* overlappedBuffer = PoolManager::getInstance()->getOverlappedBufferPool().pop();

	SOCKET& connectSocket = session->getSocketHandle();

	overlappedBuffer->_session_id = session->getSessionId();
	overlappedBuffer->_type = BufferType::CONNECT;

	WSAIoctl(connectSocket, SIO_GET_EXTENSION_FUNCTION_POINTER,
		&guid, sizeof(guid),
		&connectFunc, sizeof(connectFunc),
		&dwbyte, NULL, NULL);

	if (FALSE == connectFunc(connectSocket, reinterpret_cast<SOCKADDR*>(&socketAddr),
							 sizeof(socketAddr), NULL, NULL, NULL,
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

	overlappedBuffer->_session_id = newSession->getSessionId();
	overlappedBuffer->_type = BufferType::ACCEPT;

	LPFN_ACCEPTEX acceptFunc = nullptr;

	DWORD dwbyte{ 0 };
	GUID GuidAccept = WSAID_ACCEPTEX;
	WSAIoctl(_mainSession->getSocketHandle(), SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidAccept, sizeof(GuidAccept),
		&acceptFunc, sizeof(acceptFunc),
		&dwbyte, NULL, NULL);

	// 클래스의 가상함수 테이블 메모리때문에 acceptEx에 대한 응답을 받을때 주소값이 4byte씩 밀리는 버그가 있다.
	// 무었때문이며 이것을 해결할 수 있는가..?
	acceptFunc(_mainSession->getSocketHandle(), newSession->getSocketHandle(), &overlappedBuffer->_buffer, 0
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

	if ( NULL == disconnectFunc ) 
	{
		Logger::getInstance()->log(Logger::Level::WARNING, "disconnect NULL Error");
	}
	else 
	{
		overlappedBuffer->_session_id = session->getSessionId();
		overlappedBuffer->_type = BufferType::DISCONNECT;

		int error = disconnectFunc(session->getSocketHandle(), reinterpret_cast<LPOVERLAPPED>(&overlappedBuffer->_overlapped), TF_REUSE_SOCKET, 0);
		if ( FALSE == error ) 
		{
			if (WSA_IO_PENDING != GetLastError() )
			{
				Logger::getInstance()->log(Logger::Level::WARNING, "Disconnect Error");
				return false;
			}
		}
	}

	return true;
}

void Iocp::recv(Session* session)
{
	OverlappedBuffer* overlappedBuffer = PoolManager::getInstance()->getOverlappedBufferPool().pop();

	DWORD flag{ 0 };

	overlappedBuffer->_session_id = session->getSessionId();
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

void Iocp::send(Session* session)
{
	OverlappedBuffer* overlappedBuffer = PoolManager::getInstance()->getOverlappedBufferPool().pop();
	char s[MAX_BUFFER];

	overlappedBuffer->_session_id = session->getSessionId();
	overlappedBuffer->_type = BufferType::SEND;

	std::string word = { "HELLO Client Id : " };

	word += std::to_string(session->getSessionId());
	
	for (int i = 0; i < word.size() + 1; ++i) 
	{
		s[i] = word[i];
	}

	memcpy(overlappedBuffer->_buffer, &s, MAX_BUFFER);

	WSASend(session->getSocketHandle(), &overlappedBuffer->_wsaBuffer, 1, 0, 0, &overlappedBuffer->_overlapped, NULL);
}

void Iocp::addSession(Session* session)
{
	const bool result = CreateIoCompletionPort((HANDLE)session->getSocketHandle(), _handle, session->getSessionId(), _threadCount);

	if (false == result)
	{
		Logger::getInstance()->log(Logger::Level::WARNING, "IOCP add failed!");
	}

	_sessionList.insert(std::make_pair(session->getSessionId(), session));
}

void Iocp::getEvent(IocpEvents& output, int timeoutMs)
{
	const bool result = GetQueuedCompletionStatusEx(_handle, output.m_events, Iocp::MAX_EVENT_COUNT, (ULONG*)&output.m_eventCount, timeoutMs, FALSE);
	if (false == result)
	{
		//cout << "IOCP getEvent failed!" << endl;
		output.m_eventCount = 0;
	}
}

void Iocp::workerThread()
{
	while (true) 
	{
		DWORD		io_byte{};
		ULONGLONG	id{}; //x64

		IocpEvents readEvents;
		getEvent(readEvents, 0);

		// 받은 이벤트 각각을 처리합니다.
		for (int index = 0; index < readEvents.m_eventCount; ++index)
		{
			OVERLAPPED_ENTRY& readEvent = readEvents.m_events[index];
			OverlappedBuffer* overlappedBuffer = reinterpret_cast<OverlappedBuffer*>(readEvent.lpOverlapped);

			Session* onEventSession = _sessionList[overlappedBuffer->_session_id];

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

					//정보 얻기
					GetAcceptExSockaddrs(
						&overlappedBuffer->_buffer, 0,
						sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16,
						&pLocalSocketAddr, &pLocalSocketAddrLength, &pRemoteSocketAddr, &pRemoteSocketAddrLength);

					//SOCKADDR_IN remoteAddr = *(reinterpret_cast<PSOCKADDR_IN>(pRemoteSocketAddr));
					//접속한 클라이언트 IP와 포트 정보 얻기
					std::string connectStr = "Accept New Clients ID: " + std::to_string(overlappedBuffer->_session_id);

					recv(onEventSession);
					send(onEventSession);
					accept();
				}
				break;
				case BufferType::SEND:
				{

				}
				break;
				case BufferType::RECV:
				{
					Logger::getInstance()->log(Logger::Level::DEBUG, overlappedBuffer->_wsaBuffer.buf);

					send(onEventSession);
					recv(onEventSession);
				}
				break;
				case BufferType::DISCONNECT:
				{
					PoolManager::getInstance()->getSessionPool().push(onEventSession);
				}
				break;
				case BufferType::CONNECT:
				{

				}
				break;
			}

			PoolManager::getInstance()->getOverlappedBufferPool().push(overlappedBuffer);
		}
	}
}
