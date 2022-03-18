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
	void init();

	// 파괴될때
	void release();

	// pop
	void active();

	// push
	void deactive();


private:
	Session_ID _sessionId = undefinedSessionId;
};

