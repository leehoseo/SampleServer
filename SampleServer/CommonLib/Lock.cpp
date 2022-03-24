#include "Lock.h"
#include "Logger.h"

std::atomic<int> Lock::_lockCount = 0;

Lock::Lock()
{
}

Lock::~Lock()
{
}

void Lock::lock()
{
	// 락이 한개 이상 걸려있다면 에러
	// 다른 스래드에서, 다른lock객체를 사용할때도 에러 발생 허용해도 되는 룰이 잡히기 전까진 주석처리해놓자
	/*if (0 < _lockCount)
	{
		Logger::getInstance()->log(Logger::Level::WARNING, "Lock이 이중으로 걸렸습니다. 꼭 확인해야합니다.");
	}*/

	_lockCount.fetch_add(1);
	_lock.lock();
}

void Lock::unlock()
{
	_lock.unlock();
	_lockCount.fetch_sub(1);
}

std::mutex& Lock::get()
{
	return _lock;
}
