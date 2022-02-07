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
	unordered_map<ULONG_PTR, Socket*> socketList;
	Socket* listenSocket = new TcpSocket("127.0.0.1", 5555);
	listenSocket->bind();
	listenSocket->listen();

	//SOCKET hServSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	//SOCKADDR_IN servAddr;
	//servAddr.sin_family = AF_INET;
	//servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	////servAddr.sin_port = htons(atoi("2738"));
	//servAddr.sin_port = htons(5555);

	//bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr));
	//listen(hServSock, 5);


	Socket* waitingSocket = nullptr;

	Socket* newSocket = new TcpSocket();

	SOCKADDR_IN clntAddr;
	int addrLen = sizeof(clntAddr);

	/*newSocket->_socketHandle = accept(listenSocket->_socketHandle, (SOCKADDR*)&clntAddr, &addrLen);
	newSocket->_address._sockAddress = clntAddr;*/
	const bool result = CreateIoCompletionPort((HANDLE)listenSocket->_socketHandle, iocp._iocpHandle, (DWORD)currentlpCompletionKey, 0);
	listenSocket->acceptOverlapped(newSocket);
	socketList.insert(make_pair(currentlpCompletionKey++, listenSocket));

	//const bool result = CreateIoCompletionPort((HANDLE)newSocket->_socketHandle, iocp._iocpHandle, (DWORD)currentlpCompletionKey, 0);


	//socketList.insert( make_pair(currentlpCompletionKey, newSocket));

	//newSocket->receiveOverlapped();

	if (false == result)
	{
		cout << "IOCP add failed!" << endl;
	}

	//iocp.AddSocket(listenSocket, nullptr);
	waitingSocket = newSocket;

	//if (false == listenSocket.acceptOverlapped(*newSocket))
	//{
	//	//listenSocket.Close();
	//}

	//listenSocket.setIsOverlapping(true);

	while (true)
	{
		IocpEvents readEvents;
		//iocp.getEvent(readEvents, 0);


		const bool result = GetQueuedCompletionStatusEx(iocp._iocpHandle, readEvents.m_events, Iocp::MAX_EVENT_COUNT, (ULONG*)&readEvents.m_eventCount, 0, FALSE);
		if (false == result)
		{
			continue;
			//cout << "IOCP getEvent failed!" << endl;
			//output.m_eventCount = 0;
		}

		//GetQueuedCompletionStatus(iocp._iocpHandle, &BytesTransferred, (LPDWORD)&PerHandleData, (LPOVERLAPPED*)&PerIoData, INFINITE);

		// I/O �Ϸ� �̺�Ʈ�� ���� ������ ��ٸ��ϴ�.

		// ���� �̺�Ʈ ������ ó���մϴ�.
		for (int index = 0; index < readEvents.m_eventCount; ++index)
		{
			OVERLAPPED_ENTRY& readEvent = readEvents.m_events[index];

			// ���������̸� 0�̴�.
			if (0 == readEvent.lpCompletionKey)
			{
				listenSocket->setIsOverlapping(false);

				if (0 != waitingSocket->updateAcceptContext(listenSocket))
				{
					//listenSocket.Close();
				}
				else
				{
					const bool result = CreateIoCompletionPort((HANDLE)waitingSocket->_socketHandle, iocp._iocpHandle, (DWORD)currentlpCompletionKey, 0);
					socketList.insert(make_pair(currentlpCompletionKey++, waitingSocket));
					waitingSocket->receiveOverlapped();

					Socket* newSocket = new TcpSocket();
					waitingSocket = newSocket;

					listenSocket->acceptOverlapped(newSocket);
					////iocp.AddSocket(*waitingSocket, nullptr);
					//if (0 != waitingSocket->receiveOverlapped()) // I/O ���� ��û ��
					//{
					//	//listenSocket.Close();
					//}
					//else
					//{
					//	waitingSocket->setIsOverlapping(true);
					//	//socketList.push_back(*waitingSocket);

					//	Socket* newSocket = new TcpSocket();
					//	waitingSocket = newSocket;

					//	if (false == listenSocket->acceptOverlapped(waitingSocket))
					//	{
					//		//listenSocket.Close();
					//	}
					//	else
					//	{
					//		//listenSocket.setIsOverlapping(true);
					//	}
					//	waitingSocket->receiveOverlapped();
					//	socketList.insert(make_pair(currentlpCompletionKey++, waitingSocket));
					//}
				}
			}
			else // ����� ����
			{
				// ���� �����͸� �״�� ȸ���Ѵ�.
				//auto finder = socketList.find(readEvent.lpCompletionKey);
				Socket* clientSocket = socketList[readEvent.lpCompletionKey];

				if (readEvent.dwNumberOfBytesTransferred <= 0)
				{
					int a = 0;
				}

				//if (remoteClient)
				{
					// �̹� ���ŵ� �����̴�. ���� �Ϸ�� ���� �׳� ���� ����.
					clientSocket->setIsOverlapping(false);
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
						//char* echoData = nullptr;
						// clientSocket.getReceiveBuffer(echoData);

						//int echoDataLength = ec;

						//// ��Ģ��ζ�� TCP ��Ʈ�� Ư���� �Ϻθ� �۽��ϰ� �����ϴ� ��쵵 ����ؾ� �ϳ�,
						//// ������ ������ ���ذ� �켱�̹Ƿ�, �����ϵ��� �Ѵ�.
						//// ��Ģ��ζ�� ���⼭ overlapped �۽��� �ؾ� ������ 
						//// ������ ���ظ� ���ؼ� �׳� ���ŷ �۽��� �Ѵ�.
						clientSocket->setSendBuffer("Hellooooo");
						clientSocket->sendOverlapped();

						// �ٽ� ������ �������� overlapped I/O�� �ɾ�� �Ѵ�.
						if (clientSocket->receiveOverlapped() != 0
							&& WSAGetLastError() != ERROR_IO_PENDING)
						{
							//ProcessClientLeave(remoteClient);
						}
						else
						{
							// I/O�� �ɾ���. �ϷḦ ����ϴ� �� ���·� �ٲ���.
							clientSocket->setIsOverlapping(true);
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

int main()
{
	iocpTest2();

	return 0;
}
