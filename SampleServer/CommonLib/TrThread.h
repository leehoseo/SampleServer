#pragma once
#include "Thread.h"
#include "Tr.h"

class TrThread : public Thread
{
public: 
	TrThread(const ThreadType& type );
	virtual ~TrThread();

public:
	virtual bool work();
	virtual bool checkWaitExitCondition();	// 기본바로 wait을 탈출한다.
};

