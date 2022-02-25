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
	_eventList.push(event);
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

		// �ð��� �ȵ����� �н�
		//if (event->_timer < getCurrentTimeTick64())
		//{
		//	return;
		//}

		outEvent = _eventList.top();
		_eventList.pop();
	}
	return outEvent;
}

void Dispatcher::execute()
{
	Event* event = pop();

	if (nullptr == event)
	{
		// ������ ���� ����
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

	if (nullptr == handle)
	{
		delete event;
		return; // ���� Event ������ �ȵ�
	}

	handle->process(event);

	// �ƾƾƾ� �̷��͵� Pool�� ������ �ұ�..?
	delete event;
	delete handle;
}
