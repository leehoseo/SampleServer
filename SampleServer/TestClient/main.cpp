#include "Iocp.h"
#include "ClientIocp.h"

int main()
{
	WSADATA w;
	WSAStartup(MAKEWORD(2, 2), &w);

	Iocp* iocp = new ClientIocp();

	iocp->run();

	WSACleanup();

    return 0;
}
