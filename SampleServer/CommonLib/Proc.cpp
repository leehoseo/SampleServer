#include "Proc.h"

// procList�б� ���̶� ������ ����
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
