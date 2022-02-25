#include "TrThread.h"
#include "TrQueueManager.h"
#include "Actor.h"
#include "NetworkContents.h"
#include "SystemManager.h"

#pragma optimize("", off)

TrThread::TrThread(const ThreadType& type)
	: Thread(type)
{
}

TrThread::~TrThread()
{

}

bool TrThread::work()
{
	Actor* mainActor = SystemManager::getInstance()->getMainActor();
	NetworkContents* contents = static_cast<NetworkContents*>(mainActor->getContents(ContentsType::eNetwork));
	Tr* tr = TrQueueManager::getInstance()->pop(_type);

	if (nullptr == tr)
	{
		return true;
	}

	contents->recvTr(tr);

	delete tr;
	return true;
}

bool TrThread::checkWaitExitCondition()
{
	return 	TrQueueManager::getInstance()->isExist(_type);
}