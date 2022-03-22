#pragma once

class Actor;

enum class ContentsType
{
	eNetwork = 0,
	eThread,
	eCount,
};

class Contents
{
public:
	Contents();
	virtual ~Contents();

public: 
	virtual const ContentsType getType() = 0;

	virtual void init();
	virtual void active(Actor* owner);
	virtual void deactive();
	Actor* getOwner();

	bool isValid();

protected:
	Actor* _owner = nullptr;
};

