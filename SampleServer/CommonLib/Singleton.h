#pragma once

template< typename T>
class Singleton
{
protected:
	Singleton() {};

public:
	static T getInstance() // �����Ҵ��� �ʿ�� ����δ�.
	{
		static T _instance;

		return _instance;
	}
};

