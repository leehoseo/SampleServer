#pragma once
#include<mutex>
#include <atomic>

// Ŭ������ ���� ����
// Lock ��ü�� ���� ī���� ������ �߰��ؼ� ������� �����Ұ���
class Lock
{
public:
	Lock();
	~Lock();

	void lock();
	void unlock();
	std::mutex& get();

private:
	std::mutex _lock;
	static std::atomic<int> _lockCount;
};