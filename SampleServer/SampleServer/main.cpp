#include "SystemManager.h"
#include "Iocp.h"
#include "ServerIocp.h"

int main()
{
	WSADATA w;
	WSAStartup(MAKEWORD(2, 2), &w);

	Iocp* iocp = new ServerIocp();

	iocp->run();

	WSACleanup();

	return 0;
}
