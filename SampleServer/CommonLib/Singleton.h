#pragma once

template< typename T>
class Singleton
{
protected:
	Singleton() {};

public:
	static T getInstance() // 동적할당할 필요는 없어보인다.
	{
		static T _instance;

		return _instance;
	}
};

