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
	// ���� �Ѱ� �̻� �ɷ��ִٸ� ����
	// �ٸ� �����忡��, �ٸ�lock��ü�� ����Ҷ��� ���� �߻� ����ص� �Ǵ� ���� ������ ������ �ּ�ó���س���
	/*if (0 < _lockCount)
	{
		Logger::getInstance()->log(Logger::Level::WARNING, "Lock�� �������� �ɷȽ��ϴ�. �� Ȯ���ؾ��մϴ�.");
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
