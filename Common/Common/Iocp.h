#pragma once
#include "Base.h"
#include "Socket.h"

class Iocp
{
public:
	Iocp();
	~Iocp();

public:
	void Add(Socket& socket, void* userPtr);
private:

};

