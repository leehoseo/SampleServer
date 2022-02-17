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

	// bind�� connect ������ �ٸ��� �־�� �Ѵ� �ֿ��������ĤĤĤ�
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
	TrChatReq chatReq;
	chatReq.set(9999, "�ȳ��Ͻ���");

	send(_mainSession, &chatReq);
}

void ClientIocp::recvTr( Tr* tr)
{
}
