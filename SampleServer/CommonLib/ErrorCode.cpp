#include "ErrorCode.h"

const char* convertErrorToString(const ErrorCode& code)
{
	static const char* list[] =
	{
		"SUCCESS",
		"ERROR_INVALIED_PLAYER",
	};

	return list[static_cast<int>(code)];
}
