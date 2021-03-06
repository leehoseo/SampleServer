#include "Iocp.h"
#include "ClientIocp.h"
#include "ClientActor.h"
#include "Dispatcher.h"
#include "SystemManager.h"
#include "TrChat.h"
int main()
{
	WSADATA w;
	WSAStartup(MAKEWORD(2, 2), &w);

	SystemManager::getInstance()->init(new ClientActor(), new ClientIocp());
	SystemManager::getInstance()->insertAndRunThread();

	Iocp* iocp = SystemManager::getInstance()->getIcop();
	iocp->init();
	
	// 요건 쓰래드로 빼 말아
	while (true)
	{
		iocp->execute();
		Dispatcher::getInstance()->execute();
	}

	WSACleanup();

    return 0;
}
