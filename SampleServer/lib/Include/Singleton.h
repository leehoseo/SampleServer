#pragma once

template< typename T>
class Singleton
{
protected:
	Singleton() {};

public:
	virtual ~Singleton() {};

public:
	static T* getInstance() // �����Ҵ��� �ʿ�� ����δ�.
	{
		static T instance;

		return &instance;
	}
};

