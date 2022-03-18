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
	// ������ �ʱ�ȭ �Ǵ� �����ö�
	virtual void init();

	// �ı��ɶ�
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

