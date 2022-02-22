#pragma once
#include "ThreadContents.h"

class ServerThreadContents : public ThreadContents
{
public:
	ServerThreadContents();
	virtual ~ServerThreadContents();

public:
	virtual void insertAndRunThread();
};

