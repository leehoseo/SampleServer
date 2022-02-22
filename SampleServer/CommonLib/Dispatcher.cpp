#include "Dispatcher.h"
#include "Time.h"
#include "TrEvent.h"

Dispatcher::Dispatcher()
{
}

void Dispatcher::push(Event* event)
{
	_eventList.push(event);
}

void Dispatcher::pop(Event* outEvent)
{
	if (true == _eventList.empty())
	{
		return;
	}

	Event* event = _eventList.top();

	// 시간이 안됐으면 패스
	if (event->_timer < getCurrentTimeTick64())
	{
		return;
	}

	outEvent = event;
	_eventList.pop();
}

void Dispatcher::run()
{
	while (true)
	{
		Event* event = nullptr;
		pop(event);

		if (nullptr == event)
		{
			// 쓰레드 대기로 변경
			continue;
		}

		EventHandle* handle = nullptr;

		switch (event->_type)
		{
			case EventType::Tr: handle = new TrEventHandle(); break;
			case EventType::Action: break;
			case EventType::Logger:	break;
			case EventType::Count:	break;
			default:				break;
		}
		
		if ( nullptr == handle )
		{
			delete event;
			continue; // 아직 Event 구현이 안됨
		}

		handle->process(event);
		
		// 아아아악 이런것도 Pool로 만들어야 할까..?
		delete event;
		delete handle;
	}
}
