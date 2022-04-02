#include "TrQueueManager.h"
#include "ScopeLock.h"
#include "SystemManager.h"
#include "Actor.h"
#include "ThreadContents.h"
#include "NetworkContents.h"

#pragma optimize ("", off)

TrQueueManager::TrQueueManager()
{
}

TrQueueManager::~TrQueueManager()
{
}

void TrQueueManager::push(Tr* tr)
{
	Actor* mainActor = SystemManager::getInstance()->getMainActor();

	switch (tr->_type)
	{
		case ThreadType::eAi:
		{
			ScopeLock lock(&_aiLock);
			_aiTrList.push(tr);
		}
		break;
		case ThreadType::eAction:
		{
			ScopeLock lock(&_actionLock);
			_actionTrList.push(tr);
		}
		break;
		case ThreadType::eContents:
		{
			ScopeLock lock(&_contentsLock);
			_contentsTrList.push(tr);
		}
		break;
		case ThreadType::eClient: // 클라이언트 따로 쓰래드에 넣지않고 바로 Proc을 호출한다.
		{
			ScopeLock lock(&_clientLock);
			_clientTrList.push(tr);
		}
		break;
		case ThreadType::eCount:
		{
		}
		break;

		default:
		{

		}
		break;
	}
	
	if (ThreadType::eCount != tr->_type)
	{
		ThreadContents* contents = static_cast<ThreadContents*>(mainActor->getContents(ContentsType::eThread));
		contents->notifyOne(tr->_type);
	}
}

Tr* TrQueueManager::pop(const ThreadType& type)
{
	Tr* outTr = nullptr;
	Lock* lock = nullptr;
	std::queue<Tr*>* list = nullptr;

	switch (type)
	{
	case ThreadType::eAi:
	{
		lock = &_aiLock;
		list = &_aiTrList;
	}
	break;
	case ThreadType::eAction:
	{
		lock = &_actionLock;
		list = &_actionTrList;
	}
	break;
	case ThreadType::eContents:
	{
		lock = &_contentsLock;
		list = &_contentsTrList;
	}
	break;
	case ThreadType::eClient: // 클라이언트 따로 쓰래드에 넣지않고 바로 Proc을 호출한다.
	{
		lock = &_clientLock;
		list = &_clientTrList;
	}
	break;
	case ThreadType::eCount:
	{

	}
	break;
	default:
	{

	}
	break;
	}

	if (nullptr == lock || nullptr == list)
	{
		return nullptr;
	}

	{
		ScopeLock scopeLock(lock);

		if (true == list->empty())
		{
			return nullptr;
		}

		outTr = list->front();
		list->pop();
	}

	return outTr;
}

bool TrQueueManager::isExist(const ThreadType& type)
{
	switch (type)
	{
	case ThreadType::eAi:
	{
		ScopeLock lock(&_aiLock);
		return false == _aiTrList.empty();
	}
	break;
	case ThreadType::eAction:
	{
		ScopeLock lock(&_actionLock);
		return false == _actionTrList.empty();
	}
	break;
	case ThreadType::eContents:
	{
		ScopeLock lock(&_contentsLock);
		return false == _contentsTrList.empty();
	}
	break;
	case ThreadType::eCount:
	{

	}
	break;
	default:
	{

	}
	break;
	}

	return false;
}
