#pragma once
#include<mutex>

// Ŭ������ ���� ����
// Lock ��ü�� ���� ī���� ������ �߰��ؼ� ������� �����Ұ���
class Lock
{
public:
	Lock();
	~Lock();

	void lock();
	void unlock();

private:
	std::mutex _lock;
};

