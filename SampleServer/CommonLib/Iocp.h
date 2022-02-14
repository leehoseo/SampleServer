#pragma once
#include "Base.h"
#include "Socket.h"

class IocpEvents;
class SocketWillDelete;

class Iocp
{
public:
	// 1ȸ�� GetQueuedCompletionStatus�� �ִ��� ������ �� �ִ� ���� ����
	static const int MAX_EVENT_COUNT = 1000;

public:
	Iocp(const int threadCount = 0);
	~Iocp();

public:
	void AddSocket(SocketWillDelete& socket, void* userPtr);
	void getEvent(IocpEvents& output, int timeoutMs);

	HANDLE _iocpHandle;
private:
	int _threadCount; // IOCP ������ �� ���� �߰��� ��� ���Ǵ� ��������...
};

// IOCP�� GetQueuedCompletionStatus�� ���� I/O �Ϸ��ȣ��
class IocpEvents
{
public:
	// GetQueuedCompletionStatus���� ������ �̺�Ʈ��
	OVERLAPPED_ENTRY m_events[Iocp::MAX_EVENT_COUNT];
	int m_eventCount;
};
