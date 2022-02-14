#include "Base.h"
#include "TcpSocket.h"
#include "Socket.h"
#include "Iocp.h"
#include <vector>
#include <process.h>
#include <unordered_map>
#include "TestSample.h"

static int currentlpCompletionKey = 0;

int iocpTest()
{
	WSADATA w;
	WSAStartup(MAKEWORD(2, 2), &w);

	Iocp iocp(1);
	unordered_map<ULONG_PTR, SocketWillDelete*> socketList;
	SocketWillDelete* listenSocket = new TcpSocket("127.0.0.1", 5555);
	listenSocket->bind();
	listenSocket->listen();

	SocketWillDelete* waitingSocket = nullptr;

	SocketWillDelete* newSocket = new TcpSocket();

	SOCKADDR_IN clntAddr;
	int addrLen = sizeof(clntAddr);

	const bool result = CreateIoCompletionPort((HANDLE)listenSocket->_socketHandle, iocp._iocpHandle, (DWORD)currentlpCompletionKey, 0);
	listenSocket->acceptOverlapped(newSocket);
	socketList.insert(make_pair(currentlpCompletionKey++, listenSocket));

	if (false == result)
	{
		cout << "IOCP add failed!" << endl;
	}

	waitingSocket = newSocket;

	while (true)
	{
		IocpEvents readEvents;

		const bool result = GetQueuedCompletionStatusEx(iocp._iocpHandle, readEvents.m_events, Iocp::MAX_EVENT_COUNT, (ULONG*)&readEvents.m_eventCount, 0, FALSE);
		if (false == result)
		{
			continue;

		}

		// 받은 이벤트 각각을 처리합니다.
		for (int index = 0; index < readEvents.m_eventCount; ++index)
		{
			OVERLAPPED_ENTRY& readEvent = readEvents.m_events[index];

			// 리슨소켓이면 0이다.
			if (0 == readEvent.lpCompletionKey)
			{
				const bool result = CreateIoCompletionPort((HANDLE)waitingSocket->_socketHandle, iocp._iocpHandle, (DWORD)currentlpCompletionKey, 0);
				socketList.insert(make_pair(currentlpCompletionKey++, waitingSocket));
				waitingSocket->receiveOverlapped();

				cout << "연결 시작 " << endl;
			}
			else // 연결된 소켓
			{
				// 받은 데이터를 그대로 회신한다.
				SocketWillDelete* clientSocket = socketList[readEvent.lpCompletionKey];

				cout << "Recv :  " << clientSocket->_buffer.buf << endl;

				if (nullptr != clientSocket)
				{
					clientSocket->setSendBuffer("Hellooooo");
					clientSocket->sendOverlapped();

					clientSocket->receiveOverlapped();
				}
			}
		}
	}

	const int size = socketList.size();
	for (int index = 0; index < size; ++index)
	{
		delete(socketList[index]);
	}

	WSACleanup();
	return 0;
}

int main()
{
	iocpTest();

	return 0;
}
