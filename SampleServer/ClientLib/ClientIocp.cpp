#include "ClientIocp.h"
#include "PoolManager.h"
#include "Logger.h"

#include <WS2tcpip.h>

ClientIocp::ClientIocp()
	: Iocp(1)
{
}

ClientIocp::~ClientIocp()
{
}

void ClientIocp::runXXX()
{
	_mainSession = PoolManager::getInstance()->getSessionPool().pop();
	addSession(_mainSession);
	
	sockaddr_in server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));

	// bind와 connect 세팅을 다르게 주어야 한다 왜에에에에ㅔㅔㅔㅔ
	{
		server_addr.sin_family = PF_INET;
		server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		bind(_mainSession, server_addr);
	}

	{
		server_addr.sin_port = htons(5555);
		inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr.s_addr);
		connect(_mainSession, server_addr);
	}

	recv(_mainSession);

	//{

	//	LPFN_CONNECTEX connectFunc;

	//	DWORD dwbyte{ 0 };
	//	GUID guid = WSAID_CONNECTEX;
	//	/*SocketAddress& socketAddress = session->getSocketAddr();
	//	sockaddr_in& socketAddr = socketAddress.getSockAddress();*/
	//	OverlappedBuffer* overlappedBuffer = PoolManager::getInstance()->getOverlappedBufferPool().pop();

	//	overlappedBuffer->_session_id = clientSession->getSessionId();
	//	overlappedBuffer->_type = BufferType::CONNECT;

	//	WSAIoctl(clientSession->getSocketHandle(), SIO_GET_EXTENSION_FUNCTION_POINTER,
	//		&guid, sizeof(guid),
	//		&connectFunc, sizeof(connectFunc),
	//		&dwbyte, NULL, NULL);

	//	if (FALSE == connectFunc(clientSession->getSocketHandle(), reinterpret_cast<SOCKADDR*>(&server_addr),
	//		sizeof(server_addr), NULL, NULL, NULL,
	//		reinterpret_cast<LPOVERLAPPED>(&overlappedBuffer->_overlapped))
	//		)
	//	{
	//		auto error = GetLastError();
	//		if (WSA_IO_PENDING != error)
	//		{
	//			Logger::getInstance()->log(Logger::Level::WARNING, "Error_Connect");
	//		}
	//	}
	//}
}
