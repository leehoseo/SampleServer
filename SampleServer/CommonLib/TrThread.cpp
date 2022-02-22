#include "TrThread.h"
#include "TrQueueManager.h"

TrThread::TrThread(const TrType& type)
	: _type(type)
{
}

TrThread::~TrThread()
{

}

void TrThread::run()
{
	while (true)
	{
		Tr* tr = nullptr;
		TrQueueManager::getInstance()->pop(_type, tr);

		if (nullptr == tr)
		{
			continue;
		}

		delete tr;
	}
}
