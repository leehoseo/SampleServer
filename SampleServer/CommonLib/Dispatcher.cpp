#include "Dispatcher.h"
#include "BaseTime.h"
#include "RecvEvent.h"
#include "SendEvent.h"
#include "ScopeLock.h"

#pragma optimize("", off)

Dispatcher::Dispatcher()
{
}

void Dispatcher::push(Event* event)
{
	if (0 == event->_timer)
	{
		dispatch(event);
	}
	else
	{
		ScopeLock lock(&_lock);
		_eventList.push(event);
	}
}

Event* Dispatcher::pop()
{
	Event* outEvent = nullptr;
	{
		ScopeLock lock(&_lock);
		if (true == _eventList.empty())
		{
			return nullptr;
		}

		// 시간이 안됐으면 패스
		//if (event->_timer < getCurrentTimeTick64())
		//{
		//	return;
		//}

		outEvent = _eventList.top();
		_eventList.pop();
	}
	return outEvent;
}

void Dispatcher::dispatch(Event* event)
{
#define MAKE_EVENTHANDLE(Type) case EventType::##Type: { Type##EventHandle handle; handle.process(event); } break;
	switch (event->_type)
	{
	MAKE_EVENTHANDLE(Send)
	MAKE_EVENTHANDLE(Recv)
	}

	delete event;
}

void Dispatcher::execute()
{
	Event* event = pop();

	if (nullptr == event)
	{
		// 쓰레드 대기로 변경
		return;
	}

	dispatch(event);
}
