#pragma once
#include "Base.h"
#include "Socket.h"

class IocpEvents;
class Socket;

class Iocp
{
public:
	// 1회의 GetQueuedCompletionStatus이 최대한 꺼내올 수 있는 일의 갯수
	static const int MAX_EVENT_COUNT = 1000;

public:
	Iocp(const int threadCount = 0);
	~Iocp();

public:
	void AddSocket(Socket& socket, void* userPtr);
	void getEvent(IocpEvents& output, int timeoutMs);

private:
	HANDLE _iocpHandle;
	int _threadCount; // IOCP 생성시 및 소켓 추가시 계속 사용되는 값인지라...
};

// IOCP의 GetQueuedCompletionStatus로 받은 I/O 완료신호들
class IocpEvents
{
public:
	// GetQueuedCompletionStatus으로 꺼내온 이벤트들
	OVERLAPPED_ENTRY m_events[Iocp::MAX_EVENT_COUNT];
	int m_eventCount;
};
