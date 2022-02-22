#include "TrThread.h"
#include "TrQueueManager.h"
#include "Actor.h"
#include "NetworkContents.h"
#include "SystemManager.h"

TrThread::TrThread(const ThreadType& threadType, const TrType& type)
	: Thread(threadType)
	, _type(type)
{
}

TrThread::~TrThread()
{

}

void TrThread::run()
{
	Actor* mainActor = SystemManager::getInstance()->getMainActor();
	NetworkContents* contents = static_cast<NetworkContents*>(mainActor->getContents( ContentsType::eNetwork ) );
	while (true)
	{
		Tr* tr = nullptr;
		TrQueueManager::getInstance()->pop(_type, tr);

		if (nullptr == tr)
		{
			continue;
		}

		contents->recvTr(tr);
		
		delete tr;
	}
}
