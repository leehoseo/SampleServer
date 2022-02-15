#pragma once
#include "Singleton.h"
#include <string>

class Logger : public Singleton<Logger>
{
public:
	enum class Level
	{
		DEBUG = 0,
		WARNING = 1,
	};

public:
	Logger() {}
	virtual ~Logger() {}

public:
	void log(const Level& level, const std::string& string);
};

