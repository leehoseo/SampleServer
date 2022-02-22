#pragma once
#include "ThreadContents.h"

class ClientThreadContents : public ThreadContents
{
public:
	ClientThreadContents();
	virtual ~ClientThreadContents();

public:
	virtual void insertAndRunThread();
};

