#pragma once
#include "Base.h"
#include "Socket.h"
#include <unordered_map>
#include <WinSock2.h>
//#include <MSWSock.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"mswsock.lib")

class IocpEvents;
class Session;

class Iocp
{
public:
	// 1ȸ�� GetQueuedCompletionStatus�� �ִ��� ������ �� �ִ� ���� ����
	static const int MAX_EVENT_COUNT = 1000;

public:
	Iocp(const int threadCount = 0);
	~Iocp();

public:
	void serverRun();				// iocp�� ���� Ŭ���� �и��ؾ��Ѵ�
	void clientRun();				// iocp�� ����

	// socket �ڵ鸵
	const bool	listen(Session* session);
	const bool	bind(Session* session);
	const bool	connect(Session* session);
	const bool	accept(); // accept �غ�
	const bool	disconnect(Session* session); // disconnect �غ�
	void		recv(Session* session); // overlapeed ���� �غ� ( ��׶��忡�� ���� ó���� ��)
	void		send(Session* session); // overlapeed �۽� �غ� ( ��׶��忡�� ���� ó���� ��)

	void addSession(Session* session);
	void getEvent(IocpEvents& output, int timeoutMs);

	void workerThread();

private:
	int _threadCount; // IOCP ������ �� ���� �߰��� ��� ���Ǵ� ��������...
	HANDLE _handle;
	std::unordered_map< SESSION_ID, Session*> _sessionList;

	// listenSession�� ���� �����Ѵ�.
	Session* _listenSession = nullptr;

	int testNum = 0;
};

// IOCP�� GetQueuedCompletionStatus�� ���� I/O �Ϸ��ȣ��
class IocpEvents
{
public:
	// GetQueuedCompletionStatus���� ������ �̺�Ʈ��
	OVERLAPPED_ENTRY m_events[Iocp::MAX_EVENT_COUNT];
	int m_eventCount;
};
