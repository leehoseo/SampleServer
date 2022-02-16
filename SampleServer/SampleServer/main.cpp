#include "Iocp.h"
#include "ServerIocp.h"

int main()
{
	WSADATA w;
	WSAStartup(MAKEWORD(2, 2), &w);

	Iocp iocp(1);

	iocp.serverRun();

	WSACleanup();
	return 0;
}
