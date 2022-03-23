#include "Proc.h"

// procList읽기 전이라 문제가 있음
void ProcManager::insertProc(TrId id, Proc* proc)
{
	_procList.insert(std::make_pair(id, proc));
}

Proc* ProcManager::getProc(TrId id)
{
	auto iter = _procList.find(id);
	if (_procList.end() == iter)
	{
		return nullptr;
	}

	return iter->second;
}
