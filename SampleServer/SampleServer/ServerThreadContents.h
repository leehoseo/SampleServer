#pragma once
#include "ThreadContents.h"
#include "TrThread.h"
#include "DispatcherThread.h"

class ServerThreadContents : public ThreadContents
{
public:
	ServerThreadContents();
	virtual ~ServerThreadContents();

public:
	virtual void insertAndRunThread();
	virtual void notifyOne(const ThreadType& type);

private:
	TrThread _aiThread;
	TrThread _actionThread;
	TrThread _contentsThread;
	DispatcherThread _dispatcherThread;
};

