#include "TrQueueManager.h"
#include "ScopeLock.h"

TrQueueManager::TrQueueManager()
{
}

TrQueueManager::~TrQueueManager()
{
}

void TrQueueManager::push(Tr* tr)
{
	switch (tr->_trType)
	{
		case TrType::eAi:
		{
			ScopeLock lock(&_aiLock);
			_aiTrList.push(tr);
		}
		break;
		case TrType::eAction:
		{
			ScopeLock lock(&_actionLock);
			_actionTrList.push(tr);
		}
		break;
		case TrType::eContents:
		{
			ScopeLock lock(&_contentsLock);
			_contentsTrList.push(tr);
		}
		break;
		case TrType::eClient:
		{
			ScopeLock lock(&_clientLock); // 필요한가..?
			_clientTrList.push(tr);
		}
		break;
		case TrType::eCount:
		{

		}
		break;
		default:
		{

		}
		break;
	}
}

void TrQueueManager::pop(const TrType& type, Tr* outTr)
{
	switch (type)
	{
	case TrType::eAi:
	{
		ScopeLock lock(&_aiLock);
		outTr = _aiTrList.front();
		_aiTrList.pop();
	}
	break;
	case TrType::eAction:
	{
		ScopeLock lock(&_actionLock);
		outTr = _actionTrList.front();
		_actionTrList.pop();
	}
	break;
	case TrType::eContents:
	{
		ScopeLock lock(&_contentsLock);
		outTr = _contentsTrList.front();
		_contentsTrList.pop();
	}
	break;
	case TrType::eClient:
	{
		ScopeLock lock(&_clientLock); // 필요한가..?
		outTr = _clientTrList.front();
		_clientTrList.pop();
	}
	break;
	case TrType::eCount:
	{

	}
	break;
	default:
	{

	}
	break;
	}
}
