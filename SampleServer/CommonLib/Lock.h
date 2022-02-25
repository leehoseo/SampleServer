#pragma once
#include<mutex>

// 클래스로 감싼 이유
// Lock 객체에 대한 카운팅 로직을 추가해서 데드락을 예방할거임
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
};

