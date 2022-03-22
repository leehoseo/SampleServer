#pragma once

#include "Base.h"
#include "Socket.h"
#include <unordered_map>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"mswsock.lib")

class IocpEvents;
class Session;
class Tr;

class TrNetworkConnectReq;
class Iocp
{
public:
	// 1ȸ�� GetQueuedCompletionStatus�� �ִ��� ������ �� �ִ� ���� ����
	static const int MAX_EVENT_COUNT = 1000;

public:
	Iocp(const int threadCount = 0);
	virtual ~Iocp();

public:

	virtual void init() = 0;
	void execute();

	// socket �ڵ鸵
	const bool	listen(Session* session);
	const bool	bind(Session* session, sockaddr_in& socketAddr);
	const bool	connect(Session* session, sockaddr_in& socketAddr, TrNetworkConnectReq* tr);
	const bool	accept(); // accept �غ�
	const bool	disconnect(Session* session); // disconnect �غ�
	void		recv(Session* session); // overlapeed ���� �غ� ( ��׶��忡�� ���� ó���� ��)
	void		send(Session* session , Tr* tr); // overlapeed �۽� �غ� ( ��׶��忡�� ���� ó���� ��)
	void		send(Tr* tr); // overlapeed �۽� �غ� ( ��׶��忡�� ���� ó���� ��)
	void		send( const Session_ID sessionId , Tr* tr); // overlapeed �۽� �غ� ( ��׶��忡�� ���� ó���� ��)
	void		send( const std::vector<Session_ID> sessionIdList , Tr* tr); // overlapeed �۽� �غ� ( ��׶��忡�� ���� ó���� ��)

	void addSession(Session* session);
	void getEvent(IocpEvents& output, int timeoutMs);

	const Session_ID& getMainSessionId();

protected:
	int _threadCount; // IOCP ������ �� ���� �߰��� ��� ���Ǵ� ��������...

	HANDLE _handle;
	std::unordered_map< Session_ID, Session*> _sessionList;

	// client, Server Accept������ ���� ������ ���� �����Ѵ�.
	Session* _mainSession = nullptr;
};

// IOCP�� GetQueuedCompletionStatus�� ���� I/O �Ϸ��ȣ��
class IocpEvents
{
public:
	// GetQueuedCompletionStatus���� ������ �̺�Ʈ��
	OVERLAPPED_ENTRY m_events[Iocp::MAX_EVENT_COUNT];
	int m_eventCount;
};
