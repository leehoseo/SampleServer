#include "ClientIocp.h"
#include "PoolManager.h"
#include "Logger.h"
#include <WS2tcpip.h>

#include "TrChat.h"
#pragma optimize ("" , off )

ClientIocp::ClientIocp()
	: Iocp(1)
{}

ClientIocp::~ClientIocp()
{}

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
}


void ClientIocp::sendHelloReq()
{
	TrChatReqPacket chatReq;
	chatReq.set(9999, "안녕하쉐요");

	send(_mainSession, &chatReq);
}

void ClientIocp::recvTr( Tr* tr)
{
}
