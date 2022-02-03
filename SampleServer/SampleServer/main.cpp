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
		// I/O �Ϸ� �̺�Ʈ�� ���� ������ ��ٸ��ϴ�.
		IocpEvents readEvents;
		iocp.getEvent(readEvents, 100);

		// ���� �̺�Ʈ ������ ó���մϴ�.
		for (int index = 0; index < readEvents.m_eventCount; ++index)
		{
			OVERLAPPED_ENTRY& readEvent = readEvents.m_events[index];

			// ���������̸� 0�̴�.
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
					if (0 != waitingSocket->receiveOverlapped()) // I/O ���� ��û ��
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
			else // ����� ����
			{
				// ���� �����͸� �״�� ȸ���Ѵ�.
				Socket& clientSocket = socketList[readEvent.lpCompletionKey];
				if (readEvent.dwNumberOfBytesTransferred <= 0)
				{
					int a = 0;
				}


				//if (remoteClient)
				{
					// �̹� ���ŵ� �����̴�. ���� �Ϸ�� ���� �׳� ���� ����.
					clientSocket.setIsOverlapping(false);
					int ec = readEvent.dwNumberOfBytesTransferred;

					if (ec <= 0)
					{
						// ���� ����� 0 �� TCP ������ ������...
						// Ȥ�� ���� �� ���� ������ �� �����̴�...
						//ProcessClientLeave(remoteClient);
					}
					else
					{
						// �̹� ���ŵ� �����̴�. ���� �Ϸ�� ���� �׳� ���� ����.
						char* echoData = nullptr;
						clientSocket.getReceiveBuffer(echoData);

						int echoDataLength = ec;

						// ��Ģ��ζ�� TCP ��Ʈ�� Ư���� �Ϻθ� �۽��ϰ� �����ϴ� ��쵵 ����ؾ� �ϳ�,
						// ������ ������ ���ذ� �켱�̹Ƿ�, �����ϵ��� �Ѵ�.
						// ��Ģ��ζ�� ���⼭ overlapped �۽��� �ؾ� ������ 
						// ������ ���ظ� ���ؼ� �׳� ���ŷ �۽��� �Ѵ�.
						clientSocket.setSendBuffer(echoData);
						clientSocket.sendOverlapped();

						// �ٽ� ������ �������� overlapped I/O�� �ɾ�� �Ѵ�.
						if (clientSocket.receiveOverlapped() != 0
							&& WSAGetLastError() != ERROR_IO_PENDING)
						{
							//ProcessClientLeave(remoteClient);
						}
						else
						{
							// I/O�� �ɾ���. �ϷḦ ����ϴ� �� ���·� �ٲ���.
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
