#pragma once
class Thread
{
public:
	Thread();
	virtual ~Thread();

public:
	virtual void run() = 0;
};
