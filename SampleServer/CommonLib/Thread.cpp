#include "Thread.h"
#include <Windows.h>
#include <condition_variable>
#include <processthreadsapi.h>
#include "ScopeLock.h"

#pragma optimize("", off)

const wchar_t* getThreadStr(const ThreadType& type)
{
	switch (type)
	{
	case ThreadType::eAi:
		return L"Ai";
	case ThreadType::eAction:
		return L"Action";
	case ThreadType::eContents:
		return L"Contents";
	case ThreadType::eCount:
		return L"None";
	default:
		break;
	}
}

Thread::Thread(const ThreadType& type)
	: _type(type)
{
}

Thread::~Thread()
{
	const int size = _threadList.size();

	for (int index = 0; index < size; ++index)
	{
		_threadList[index].detach();
	}
}

void Thread::init(const int threadCount)
{
	for (int index = 0; index < threadCount; ++index)
	{
		//std::thread thread(&Thread::run, this);
		_threadList.emplace_back(std::thread(&Thread::run, this));
	}
}

bool Thread::work()
{
	return false;
}

int num = 0;
void Thread::run()
{
	PCWSTR threadName = getThreadStr(getType());
	SetThreadDescription(GetCurrentThread() , threadName);

	while (true)
	{
		{
			// 이건 LockCount 검증을 어떻게 할까...
			std::unique_lock<std::mutex> lock(_lock.get());
			_condition.wait(lock, [&]()
				{
					return checkWaitExitCondition();
				});
		}

		const bool result = work();

		if ( false == result)
		{ 
			break;
		}
	}
}

void Thread::notifyOne()
{
	std::unique_lock<std::mutex> lock(_lock.get());
	_condition.notify_one();
}
