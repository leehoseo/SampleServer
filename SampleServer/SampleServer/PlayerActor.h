#pragma once
#include "CharacterActor.h"
#include "Base.h"
#include <string>

class PlayerActor : public CharacterActor
{
public:
	PlayerActor();
	virtual ~PlayerActor();

	const SessionKey& getSessionKey();
	void			  setSessionKey(const SessionKey& sessionKey);


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
	SessionKey _sessionKey;
};

