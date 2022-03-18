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
private:

	std::string _name;
};

