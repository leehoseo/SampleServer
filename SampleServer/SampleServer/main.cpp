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
	//TrQueueManager::getInstance()->init();

	Iocp* iocp = SystemManager::getInstance()->getIcop();
	iocp->init();

	SystemManager::getInstance()->insertAndRunThread();

	WSACleanup();

	return 0;
}
