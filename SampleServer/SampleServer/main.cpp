#include "Base.h"
#include "TcpSocket.h"
#include "Socket.h"
#include "Iocp.h"
#include <vector>

#pragma optimize("",off)

int main()
{
	WSADATA w;
	WSAStartup(MAKEWORD(2, 2), &w);

	Iocp iocp(1);
	vector<Socket> socketList;
	TcpSocket listenSocket("127.0.0.1", 5555);
	listenSocket.bind();
	listenSocket.listen();
	iocp.AddSocket(listenSocket, nullptr);
	
	Socket* waitingSocket = nullptr;

	{
		Socket* newSocket = new TcpSocket();
		waitingSocket = newSocket;

		if (false == listenSocket.acceptOverlapped(*newSocket))
		{
			//listenSocket.Close();
		}
	}

	listenSocket.setIsOverlapping(true);

	while (true)
	{
		// I/O 완료 이벤트가 있을 때까지 기다립니다.
		IocpEvents readEvents;
		iocp.getEvent(readEvents, 100);

		// 받은 이벤트 각각을 처리합니다.
		for (int index = 0; index < readEvents.m_eventCount; ++index)
		{
			OVERLAPPED_ENTRY& readEvent = readEvents.m_events[index];

			// 리슨소켓이면 0이다.
			if (0 == readEvent.lpCompletionKey)
			{
				listenSocket.setIsOverlapping(false);

				if (0 != waitingSocket->updateAcceptContext(listenSocket))
				{
					//listenSocket.Close();
				}
				else
				{
					iocp.AddSocket(*waitingSocket, nullptr);
					if (0 != waitingSocket->receiveOverlapped()) // I/O 수신 요청 함
					{
						//listenSocket.Close();
					}
					else
					{
						waitingSocket->setIsOverlapping(true);
						socketList.push_back(*waitingSocket);

						Socket* newSocket = new Socket();
						waitingSocket = newSocket;

						if (false == listenSocket.acceptOverlapped(*waitingSocket))
						{
							//listenSocket.Close();
						}
						else
						{
							listenSocket.setIsOverlapping(true);
						}

					}
				}
			}
			else // 연결된 소켓
			{
				// 받은 데이터를 그대로 회신한다.
				Socket& clientSocket = socketList[readEvent.lpCompletionKey];
				if (readEvent.dwNumberOfBytesTransferred <= 0)
				{
					int a = 0;
				}


				//if (remoteClient)
				{
					// 이미 수신된 상태이다. 수신 완료된 것을 그냥 꺼내 쓰자.
					clientSocket.setIsOverlapping(false);
					int ec = readEvent.dwNumberOfBytesTransferred;

					if (ec <= 0)
					{
						// 읽은 결과가 0 즉 TCP 연결이 끝났다...
						// 혹은 음수 즉 뭔가 에러가 난 상태이다...
						//ProcessClientLeave(remoteClient);
					}
					else
					{
						// 이미 수신된 상태이다. 수신 완료된 것을 그냥 꺼내 쓰자.
						char* echoData = nullptr;
						clientSocket.getReceiveBuffer(echoData);

						int echoDataLength = ec;

						// 원칙대로라면 TCP 스트림 특성상 일부만 송신하고 리턴하는 경우도 고려해야 하나,
						// 지금은 독자의 이해가 우선이므로, 생략하도록 한다.
						// 원칙대로라면 여기서 overlapped 송신을 해야 하지만 
						// 독자의 이해를 위해서 그냥 블로킹 송신을 한다.
						clientSocket.setSendBuffer(echoData);
						clientSocket.sendOverlapped();

						// 다시 수신을 받으려면 overlapped I/O를 걸어야 한다.
						if (clientSocket.receiveOverlapped() != 0
							&& WSAGetLastError() != ERROR_IO_PENDING)
						{
							//ProcessClientLeave(remoteClient);
						}
						else
						{
							// I/O를 걸었다. 완료를 대기하는 중 상태로 바꾸자.
							clientSocket.setIsOverlapping(true);
						}
					}
				}
			}
		}
	}

	//const int size = socketList.size();
	//for (int index = 0; index < size; ++index)
	//{
	//	delete(socketList[index]);
	//}
	//delete(listenSocket);

	WSACleanup();
	return 0;
}
