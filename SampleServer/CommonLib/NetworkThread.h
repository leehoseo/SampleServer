#pragma once
#include "Thread.h"

class NetworkThread : public Thread
{
public:
	NetworkThread();
	virtual ~NetworkThread();

public:
	virtual bool work();
	virtual bool checkWaitExitCondition();	// �⺻�ٷ� wait�� Ż���Ѵ�.
};

