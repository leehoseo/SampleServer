#pragma once
#include "Base.h"
#include "Contents.h"
#include <unordered_map>

class Actor
{
public:
	Actor();
	~Actor();
public:
	// 생성시 초기화 또는 가져올때
	virtual void init();

	// 파괴될때
	virtual void release();

	// pop
	virtual void active();

	// push
	virtual void deactive();

public:
	const ActorKey& getActorKey();
public:
	Contents* getContents(const ContentsType& type);

protected:
	void insertContents(Contents* contents );

private:
	std::unordered_map<ContentsType, Contents*> _contentsList;

	ActorKey _actorKey = undefinedActorKey;
};

