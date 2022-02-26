#include "ServerIocp.h"
#include "PoolManager.h"

ServerIocp::ServerIocp()
	: Iocp(1)
{

}

ServerIocp::~ServerIocp()
{

}

void ServerIocp::init()
{
	// 서버에서 사용할 세션 생성
	_mainSession = PoolManager::getInstance()->getSessionPool().pop();
	addSession(_mainSession);

	sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(13481);

	bind(_mainSession, server_addr);
	listen(_mainSession);

	accept();
}