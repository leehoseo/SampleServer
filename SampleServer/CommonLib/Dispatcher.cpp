#include "Dispatcher.h"
#include "BaseTime.h"
#include "RecvEvent.h"
#include "SendEvent.h"
//#include "ScopeLock.h"

#pragma optimize("", off)

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

void Dispatcher::execute()
{
	//while (true)
	{
		Event* event = nullptr;
		pop(event);

		if (nullptr == event)
		{
			// 쓰레드 대기로 변경
			return;
		}

		EventHandle* handle = nullptr;

#define CaseHandle(Type) case EventType::##Type: handle = new Type##EventHandle(); break;

		switch (event->_type)
		{
			CaseHandle(Recv);
			CaseHandle(Send);
			default: break;
		}
		
		if ( nullptr == handle )
		{
			delete event;
			return; // 아직 Event 구현이 안됨
		}

		handle->process(event);
		
		// 아아아악 이런것도 Pool로 만들어야 할까..?
		delete event;
		delete handle;
	}
}
