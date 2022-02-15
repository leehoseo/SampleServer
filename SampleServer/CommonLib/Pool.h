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
	std::list<T*> _list;

	bool _isValid = false;
};


// �Ǵµ��� �س��� hpp�� ���� ���� �����. ���߿� ���ľ���
template< typename T>
Pool<T>::Pool()
{
	_isValid = false;
}

template< typename T>
Pool<T>::~Pool()
{
	for (auto itor = _list.begin(); itor != _list.end(); ++itor)
	{
		T* item = *itor;

		item->release();
		delete item;
	}

	_list.clear();

	_isValid = false;
}

template< typename T>
void Pool<T>::init(const int size)
{
	for (int index = 0; index < size; ++index)
	{
		T* newItem = new T();
		newItem->init();


		_list.push_back(newItem);
	}

	_isValid = true;
}

template<typename T>
void Pool<T>::push(T* item)
{
	item->deactive();
	_list.push_back(item);
}

template<typename T>
const bool Pool<T>::isValid() const
{
	return _isValid;
}

template<typename T>
T* Pool<T>::pop()
{
	T* item = _list.back();
	_list.pop_back();

	item->active();

	return item;
}