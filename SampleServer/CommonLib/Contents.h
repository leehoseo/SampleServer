#pragma once

class Actor;

enum class ContentsType
{
	eNetwork = 0,
	eThread = 0,
	eCount,
};

class Contents
{
public:
	Contents();
	virtual ~Contents();

public: 
	virtual const ContentsType getType() = 0;

	virtual void init(Actor* owner);
	Actor* getOwner();

	bool isValid();

protected:
	Actor* _owner;
};

