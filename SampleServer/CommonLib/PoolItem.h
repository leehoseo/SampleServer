#pragma once
class PoolItem
{
public:
	PoolItem();
	virtual ~PoolItem();

public:
	// 생성시 초기화 또는 가져올때
	virtual void init() = 0;

	// 파괴될때
	virtual void release() = 0;
	

	// pop
	virtual void active() = 0;

	// push
	virtual void deactive() = 0;
};

