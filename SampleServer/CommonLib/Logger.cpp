#include "Logger.h"
#include <iostream>
#include <assert.h>

void Logger::log(const Level& level, const std::string& string)
{
	switch (level)
	{
		case Level::DEBUG:
		{
			std::cout << string.c_str() << std::endl;
		}
		break;
		case Level::WARNING:
		{
			std::cout << string.c_str() << std::endl;
			__debugbreak();
		}
		break;

		default:
		{

		}
		break;
	}
}