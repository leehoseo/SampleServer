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

	// �ð��� �ȵ����� �н�
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
			// ������ ���� ����
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
			continue; // ���� Event ������ �ȵ�
		}

		handle->process(event);
		
		// �ƾƾƾ� �̷��͵� Pool�� ������ �ұ�..?
		delete event;
		delete handle;
	}
}
