#include "SystemManager.h"
#include "ServerActor.h"
#include "ServerIocp.h"
#include "Dispatcher.h"
#include "TrQueueManager.h"

int main()
{
	WSADATA w;
	WSAStartup(MAKEWORD(2, 2), &w);

	SystemManager::getInstance()->init(new ServerActor(), new ServerIocp());

	Iocp* iocp = SystemManager::getInstance()->getIcop();
	iocp->init();

	SystemManager::getInstance()->insertAndRunThread();

	while (true)
	{
		iocp->execute();
	}


	WSACleanup();

	return 0;
}
