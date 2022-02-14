#include "Iocp.h"

Iocp::Iocp(const int threadCount)
{
	_iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, threadCount);
	_threadCount = threadCount;
}

Iocp::~Iocp()
{
	CloseHandle(_iocpHandle);
}

void Iocp::AddSocket(SocketWillDelete& socket, void* userPtr)
{
	const bool result = CreateIoCompletionPort((HANDLE)socket.getHandle(), _iocpHandle, (ULONG_PTR)userPtr, _threadCount);

	if (false == result)
	{
		cout << "IOCP add failed!" << endl;
	}
}

void Iocp::getEvent(IocpEvents& output, int timeoutMs)
{
	const bool result = GetQueuedCompletionStatusEx(_iocpHandle, output.m_events, Iocp::MAX_EVENT_COUNT, (ULONG*)&output.m_eventCount, timeoutMs, FALSE);
	if (false == result)
	{
		//cout << "IOCP getEvent failed!" << endl;
		output.m_eventCount = 0;
	}
}

