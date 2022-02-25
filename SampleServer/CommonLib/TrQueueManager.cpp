#include "TrQueueManager.h"
#include "ScopeLock.h"
#include "SystemManager.h"
#include "Actor.h"
#include "ThreadContents.h"
TrQueueManager::TrQueueManager()
{
}

TrQueueManager::~TrQueueManager()
{
}

void TrQueueManager::push(Tr* tr)
{
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
		case ThreadType::eCount:
		{

		}
		break;
		default:
		{

		}
		break;

		Actor* mainActor = SystemManager::getInstance()->getMainActor();
		ThreadContents* contents = static_cast<ThreadContents*>(mainActor->getContents(ContentsType::eThread));
		contents->notifyOne(tr->_type);
	}
}

void TrQueueManager::pop(const ThreadType& type, Tr* outTr)
{
	switch (type)
	{
	case ThreadType::eAi:
	{
		ScopeLock lock(&_aiLock);
		outTr = _aiTrList.front();
		_aiTrList.pop();
	}
	break;
	case ThreadType::eAction:
	{
		ScopeLock lock(&_actionLock);
		outTr = _actionTrList.front();
		_actionTrList.pop();
	}
	break;
	case ThreadType::eContents:
	{
		ScopeLock lock(&_contentsLock);
		outTr = _contentsTrList.front();
		_contentsTrList.pop();
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
