#include "Tr.h"

Tr::Tr()
{
}


Tr::Tr(const TrId trId, const TrType trType, const int maxSize)
	: _trType(trType)
	, _maxSize(maxSize)
	, _trId(trId)
{
}

Tr::~Tr()
{
}
