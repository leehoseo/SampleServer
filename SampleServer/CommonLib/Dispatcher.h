#pragma once
#include "Base.h"
#include "Singleton.h"
#include "Event.h"
#include <queue>

class Dispatcher : public Singleton<Dispatcher>
{
public:
	Dispatcher();
	virtual ~Dispatcher() {}

public:
	void push( Event* event );

private:
	std::priority_queue<Event*> _eventList;
	
private:
	void pop( Event* outEvent );
	void run();
};

