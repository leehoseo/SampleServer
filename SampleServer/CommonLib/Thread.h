#pragma once
#include <condition_variable>
#include <thread>
#include <vector>
#include "Lock.h"

enum class ThreadType
{
	// Tr ó����
	eAi = 0,
	eAction,
	eContents,
	eNetwork,
	eDispatcher,

	eCount,
};

class Thread
{
public:
	Thread(const ThreadType& type);
	virtual ~Thread();

public:
	void init(const int threadCount);

	virtual bool work();
	void run();
	const ThreadType& getType() { return _type; };

	virtual bool checkWaitExitCondition() { return true; };	// �⺻�ٷ� wait�� Ż���Ѵ�.
	void		notifyOne();
protected:
	std::condition_variable _condition;
	ThreadType _type;
	Lock _lock;

private:
	std::vector<std::thread> _threadList;
};
