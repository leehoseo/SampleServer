#pragma once
#include "Base.h"
#include "Field.h"
#include "Singleton.h"
#include <unordered_map>

class FieldManager : public Singleton<FieldManager>
{
public:
	FieldManager();
	~FieldManager();

	void init();
	Field* getField(const FieldType& type, const FieldKey key);
	Field* getAccessibleField(const FieldType& type);

private:
	typedef std::unordered_map<FieldKey::Type, Field*> FieldList;
	typedef std::unordered_map<FieldType, FieldList> FieldTypeList;

	FieldTypeList _fieldTypeList;
};

