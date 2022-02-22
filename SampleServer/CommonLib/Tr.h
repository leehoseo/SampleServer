#pragma once
#include "TrId.h"

enum class TrType
{
	eAi = 0,	// �������� �ַ� ����ϴ� trType
	eAction,	// �̵�, ���ݵ� ���� ���伺�� �ʿ�� �ϴ� trType
	eContents,	// ������ ȹ��, �Ǹ� �� ���伺�� ������ �ʾƵ� �Ǵ� trType
	eClient,	// Ŭ���̾�Ʈ�� trType�� ���� �ʿ�� ����
	eCount,
};


class Tr
{
public:
	Tr();
	Tr( const TrId trId, const TrType trType, const int maxSize );
	~Tr();

public:
	TrId		_trId;		// ��� �����忡�� ������
	TrType		_trType;		// ��� �����忡�� ������
	int			_maxSize;		// Ŭ������ �ִ� ũ�� ������
};