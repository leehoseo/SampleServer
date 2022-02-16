#include "ServerIocp.h"
#include "PoolManager.h"

ServerIocp::ServerIocp()
	: Iocp(1)
{

}

ServerIocp::~ServerIocp()
{

}

void ServerIocp::runXXX()
{
	// �������� ����� ���� ����
	_mainSession = PoolManager::getInstance()->getSessionPool().pop();
	addSession(_mainSession);

	sockaddr_in server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(5555);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(_mainSession, server_addr);
	listen(_mainSession);

	accept();
}