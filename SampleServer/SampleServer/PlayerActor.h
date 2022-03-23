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
	// 생성시 초기화 또는 가져올때
	virtual void init();

	// 파괴될때
	virtual void release();

	// pop
	virtual void active();

	// push
	virtual void deactive();


private:
	SessionKey _sessionKey;
};

