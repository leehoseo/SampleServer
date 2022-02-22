#pragma once
#include "Thread.h"
#include "Tr.h"

class TrThread : public Thread
{
public: 
	TrThread( const TrType& type );
	virtual ~TrThread();

public:
	virtual void run();

private:
	TrType _type;
};

