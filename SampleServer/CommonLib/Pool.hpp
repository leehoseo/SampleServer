#include "Pool.h"

template< typename T>
Pool<T>::Pool()
{
	isValid = false;
}

template< typename T>
Pool<T>::~Pool()
{
	const int size = _list.size();
	for (int index = 0; index < size; ++index)
	{
		T* item = _list[index];
		item->release();

		delete item;
	}

	isValid = false;
}

template< typename T>
void Pool<T>::init(const int size)
{
	for (int index = 0; index < size; ++index)
	{
		T* newItem = new T();
		// newItem->init(); 내부에서 한다.

		_list.push_back(newItem);
	}

	isValid = true;
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
	T* item = _list.pop_back();
	item.active();

	return item;
}
