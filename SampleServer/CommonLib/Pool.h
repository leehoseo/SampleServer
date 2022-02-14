#pragma once

#include <list>

// Lock 추가해야한다.
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

