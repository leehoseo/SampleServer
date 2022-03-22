#pragma once
#include "Actor.h"
#include <string>

class CharacterActor : public Actor
{
public:
	CharacterActor();
	virtual ~CharacterActor();

	const std::string&	getName();
	void				setName(const std::string& name);

public:
	// 생성시 초기화 또는 가져올때
	virtual void init();

	// 파괴될때
	virtual void release();

	// pop
	virtual void active();

	// push
	virtual void deactive();
private:

	std::string _name;
};

