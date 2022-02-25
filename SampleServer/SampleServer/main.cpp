#include "SystemManager.h"
#include "ServerActor.h"
#include "ServerIocp.h"
#include "Dispatcher.h"

int main()
{
	WSADATA w;
	WSAStartup(MAKEWORD(2, 2), &w);

	SystemManager::getInstance()->init(new ServerActor(), new ServerIocp());
	SystemManager::getInstance()->insertAndRunThread();

	Iocp* iocp = SystemManager::getInstance()->getIcop();
	iocp->init();

	while (true)
	{
		iocp->execute();
		Dispatcher::getInstance()->execute();
	}

	WSACleanup();

	return 0;
}
