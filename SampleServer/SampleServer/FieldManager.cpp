#include "FieldManager.h"
#include "InGameField.h"
#include "LobbyField.h"
FieldManager::FieldManager()
{

}

FieldManager::~FieldManager()
{
}

void FieldManager::init()
{
	{
		const int lobbySize = 1;
		for (int index = 0; index < lobbySize; ++index)
		{
			Field* newField = new LobbyField();
			_fieldTypeList[FieldType::eLobby].insert(std::make_pair(newField->getKey().get(), newField));
		}
	}

	{
		const int ingameSize = 2;
		for (int index = 0; index < ingameSize; ++index)
		{
			Field* newField = new InGameField();
			_fieldTypeList[FieldType::eInGame].insert(std::make_pair(newField->getKey().get(), newField));
		}
	}
}

Field* FieldManager::getField(const FieldType& type, const FieldKey key)
{
	return _fieldTypeList[type][key.get()];
}

Field* FieldManager::getAccessibleField(const FieldType& type)
{
	FieldList& fieldList = _fieldTypeList[FieldType::eInGame];

	for (auto iter = fieldList.begin(); iter != fieldList.end(); ++iter)
	{
		Field* field = iter->second;

		if (true == field->isFull())
		{
			continue;
		}

		return field;
	}

	return nullptr;
}