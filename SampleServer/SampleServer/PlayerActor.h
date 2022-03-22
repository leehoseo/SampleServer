#pragma once
#include "CharacterActor.h"
#include "Base.h"
#include <string>

class PlayerActor : public CharacterActor
{
public:
	PlayerActor();
	virtual ~PlayerActor();

	const Session_ID& getSessionId();
	void			  setSessionId(const Session_ID& sessionId);


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
	Session_ID _sessionId = undefinedSessionId;
};

