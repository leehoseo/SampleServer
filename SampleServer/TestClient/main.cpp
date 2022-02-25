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

	
	bool tester = false;

	while (true)
	{
		if (true == tester)
		{
			TrChatReq req;
			req.set(4444, "hey");
			iocp->send(&req);
		}


		iocp->execute();
		Dispatcher::getInstance()->execute();
	}

	WSACleanup();

    return 0;
}
