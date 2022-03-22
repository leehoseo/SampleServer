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
	// ������ �ʱ�ȭ �Ǵ� �����ö�
	virtual void init();

	// �ı��ɶ�
	virtual void release();

	// pop
	virtual void active();

	// push
	virtual void deactive();
private:

	std::string _name;
};

