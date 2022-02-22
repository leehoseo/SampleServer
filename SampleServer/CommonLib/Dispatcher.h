#pragma once
#include "Base.h"
#include "Singleton.h"
#include "Event.h"
#include <queue>
//#include "ScopeLock.h"

class Dispatcher : public Singleton<Dispatcher>
{
public:
	Dispatcher();
	virtual ~Dispatcher() {}

public:
	void push( Event* event );
	void execute();

private:
	void pop( Event* outEvent );

private:
	std::priority_queue<Event*> _eventList;
	//Lock _lock;
};

