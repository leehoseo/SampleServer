#include "Iocp.h"
#include "ClientIocp.h"

int main()
{
	WSADATA w;
	WSAStartup(MAKEWORD(2, 2), &w);

	Iocp iocp(1);

	iocp.clientRun();

	WSACleanup();

    return 0;
}
