#pragma once

enum class ThreadType
{
	// Tr Ã³¸®¿ë
	eAi = 0,
	eAction,
	eContents,

	eCount,
};

class Thread
{
public:
	Thread(const ThreadType& type);
	virtual ~Thread();

public:
	virtual void run() = 0;
	const ThreadType& getType() { return _type; };
	ThreadType _type;
};
