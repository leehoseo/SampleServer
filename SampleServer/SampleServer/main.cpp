#include "Base.h"
#include "TcpSocket.h"
#include "Socket.h"
#include "Iocp.h"

int main()
{
	Iocp iocp(1);
	/*Socket* listenSocket = new TcpSocket("127.0.0.1", 5555);
	listenSocket->listen();*/

	//iocp.AddSocket(*listenSocket, nullptr);


	//Socket* clientSocket = new TcpSocket();

	//listenSocket->acceptOverlapped(*clientSocket);

	//listenSocket->setIsOverlapping(true);

	//while (true)
	//{
	//	// I/O �Ϸ� �̺�Ʈ�� ���� ������ ��ٸ��ϴ�.
	//	IocpEvents readEvents;
	//	iocp.getEvent(readEvents, 100);

	//	// ���� �̺�Ʈ ������ ó���մϴ�.
	//	for (int index = 0; index < readEvents.m_eventCount; ++index)
	//	{
	//		OVERLAPPED_ENTRY& readEvent = readEvents.m_events[index];


	//	}
	//}

	//delete(listenSocket);
	//delete(clientSocket);

	return 0;
}
