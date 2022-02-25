#include "ServerThreadContents.h"
#include "TrThread.h"

#pragma optimize("", off)

ServerThreadContents::ServerThreadContents()
	:_aiThread(ThreadType::eAi)
	, _actionThread(ThreadType::eAction)
	, _contentsThread(ThreadType::eContents)
{
}

ServerThreadContents::~ServerThreadContents()
{
}

void ServerThreadContents::insertAndRunThread()
{
	{
		_aiThread.init(3);
	}
	{
		_actionThread.init(2);
	}
	{
		_contentsThread.init(2);
	}
}


void ServerThreadContents::notifyOne(const ThreadType& type)
{
	switch (type)
	{
	case ThreadType::eAi:
		_aiThread.notifyOne();
		break;
	case ThreadType::eAction:
		_actionThread.notifyOne();
		break;
	case ThreadType::eContents:
		_contentsThread.notifyOne();
		break;
	case ThreadType::eCount:
		break;
	default:
		break;
	}
}
