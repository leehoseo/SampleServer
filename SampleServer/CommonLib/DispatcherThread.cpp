#include "DispatcherThread.h"
#include "Dispatcher.h"

DispatcherThread::DispatcherThread()
	: Thread(ThreadType::eDispatcher)
{
}

DispatcherThread::~DispatcherThread()
{
}

bool DispatcherThread::work()
{
	Dispatcher::getInstance()->execute();

	// 반복 여부
	return true;
}

bool DispatcherThread::checkWaitExitCondition()
{
	// 무한 루프 돌릴거다 나중에 쓰레드 늘어나면 1ms에 한번씩정도로 변경
	return true;
}
