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
	// 1회의 GetQueuedCompletionStatus이 최대한 꺼내올 수 있는 일의 갯수
	static const int MAX_EVENT_COUNT = 1000;

public:
	Iocp(const int threadCount = 0);
	~Iocp();

public:
	void serverRun();				// iocp의 시작 클래스 분리해야한다
	void clientRun();				// iocp의 시작

	// socket 핸들링
	const bool	listen(Session* session);
	const bool	bind(Session* session);
	const bool	connect(Session* session);
	const bool	accept(); // accept 준비
	const bool	disconnect(Session* session); // disconnect 준비
	void		recv(Session* session); // overlapeed 수신 준비 ( 백그라운드에서 수신 처리를 함)
	void		send(Session* session); // overlapeed 송신 준비 ( 백그라운드에서 수신 처리를 함)

	void addSession(Session* session);
	void getEvent(IocpEvents& output, int timeoutMs);

	void workerThread();

private:
	int _threadCount; // IOCP 생성시 및 소켓 추가시 계속 사용되는 값인지라...
	HANDLE _handle;
	std::unordered_map< SESSION_ID, Session*> _sessionList;

	// listenSession은 따로 보관한다.
	Session* _listenSession = nullptr;

	int testNum = 0;
};

// IOCP의 GetQueuedCompletionStatus로 받은 I/O 완료신호들
class IocpEvents
{
public:
	// GetQueuedCompletionStatus으로 꺼내온 이벤트들
	OVERLAPPED_ENTRY m_events[Iocp::MAX_EVENT_COUNT];
	int m_eventCount;
};
