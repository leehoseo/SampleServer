#pragma once

#include <list>

// Lock �߰��ؾ��Ѵ�.
template< typename T>
class Pool
{
public:
	Pool();
	~Pool();

public:
	void init(const int size);

	void push(T* item);
	T* pop();

	const bool isValid() const;

private:
	std::list<T> _list;

	bool _isValid = false;
};

