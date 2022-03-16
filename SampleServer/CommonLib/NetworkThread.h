#pragma once
#include "Thread.h"

class NetworkThread : public Thread
{
public:
	NetworkThread();
	virtual ~NetworkThread();

public:
	virtual bool work();
	virtual bool checkWaitExitCondition();	// 기본바로 wait을 탈출한다.
};

