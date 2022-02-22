#include "Dispatcher.h"
#include "Time.h"
#include "RecvEvent.h"
#include "SendEvent.h"
//#include "ScopeLock.h"

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

	// �ð��� �ȵ����� �н�
	if (event->_timer < getCurrentTimeTick64())
	{
		return;
	}

	outEvent = event;
	_eventList.pop();
}

void Dispatcher::execute()
{
	while (true)
	{
		Event* event = nullptr;
		pop(event);

		if (nullptr == event)
		{
			// ������ ���� ����
			continue;
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
			continue; // ���� Event ������ �ȵ�
		}

		handle->process(event);
		
		// �ƾƾƾ� �̷��͵� Pool�� ������ �ұ�..?
		delete event;
		delete handle;
	}
}
