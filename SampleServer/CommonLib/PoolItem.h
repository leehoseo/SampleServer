#pragma once
class PoolItem
{
public:
	PoolItem();
	virtual ~PoolItem();

public:
	// ������ �ʱ�ȭ �Ǵ� �����ö�
	virtual void init() = 0;

	// �ı��ɶ�
	virtual void release() = 0;
	

	// pop
	virtual void active() = 0;

	// push
	virtual void deactive() = 0;
};

