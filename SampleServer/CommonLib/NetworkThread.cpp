#include "NetworkThread.h"
#include "SystemManager.h"
#include "Iocp.h"

NetworkThread::NetworkThread()
	: Thread(ThreadType::eNetwork)
{
}

NetworkThread::~NetworkThread()
{
}

bool NetworkThread::work()
{
	Iocp* iocp = SystemManager::getInstance()->getIcop();

	iocp->execute();

	// 반복 여부
	return true;
}

bool NetworkThread::checkWaitExitCondition()
{
	// 무한 루프 돌릴거다 나중에 쓰레드 늘어나면 1ms에 한번씩정도로 변경
	return true;
}
