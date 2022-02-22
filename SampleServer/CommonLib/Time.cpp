#include "Time.h"
#include <chrono>

TickCount64 getCurrentTimeTick64()
{
	return static_cast<TickCount64>(std::chrono::system_clock::now().time_since_epoch().count());
}

