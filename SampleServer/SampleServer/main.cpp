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
	//	// I/O 완료 이벤트가 있을 때까지 기다립니다.
	//	IocpEvents readEvents;
	//	iocp.getEvent(readEvents, 100);

	//	// 받은 이벤트 각각을 처리합니다.
	//	for (int index = 0; index < readEvents.m_eventCount; ++index)
	//	{
	//		OVERLAPPED_ENTRY& readEvent = readEvents.m_events[index];


	//	}
	//}

	//delete(listenSocket);
	//delete(clientSocket);

	return 0;
}
