#pragma once
#include "Contents.h"

class ThreadContents : public Contents
{
public:
	ThreadContents();
	virtual ~ThreadContents();

public:
	virtual const ContentsType getType() { return ContentsType::eThread; };
	virtual void insertAndRunThread() = 0;
};

