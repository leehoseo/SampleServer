#pragma once

enum class ErrorCode
{
	SUCCESS = 0,
	ERROR_INVALIED_PLAYER,
	eCount,
};

const char* convertErrorToString(const ErrorCode& code);
