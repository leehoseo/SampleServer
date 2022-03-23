#pragma once

#define MAX_BUFFER      1024

#pragma region keyDefine

#define MAKE_KEY(keyName , type)													\
class keyName																		\
{																					\
public:																				\
	typedef type Type;																\
	static const Type undefined = 0;												\
																					\
public:																				\
	keyName(const Type& data) : _data(data) {}										\
	keyName() : _data(undefined) {}													\
	~keyName() {};																	\
																					\
public:																				\
	const Type& get() const { return _data; }										\
	void clear() { _data = undefined; }												\
																					\
	void operator=(keyName& ref) { _data = ref._data; }								\
	void operator=(const keyName& ref) { _data = ref._data; }						\
	void operator=(Type& ref) { _data = ref; }										\
	bool operator==(const keyName& ref) const { return _data == ref._data; }		\
																					\
private:																			\
	Type _data = undefined;															\
};																					\

#pragma endregion

MAKE_KEY(ActorKey , unsigned int)
MAKE_KEY(SessionKey, unsigned int)