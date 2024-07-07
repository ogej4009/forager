#pragma once
#include <typeinfo>

// RTTI == Run Time Type Information  : 실행 도중 타입을 알아내는 방법

class GameRTTI
{
private:
	const type_info* m_TypeInfo;

public:
	const type_info* Type()
	{
		return m_TypeInfo;
	}

	bool Check(const GameRTTI& _Other)
	{
		return _Other.m_TypeInfo == m_TypeInfo;
	}

	bool Check(const type_info* _TypeInfo)
	{
		return m_TypeInfo == _TypeInfo;
	}

	template<typename T>
	bool Check()
	{
		return m_TypeInfo == &typeid(T);
	}

public:
	void TypeSetting();

	void TypeSetting(const type_info* _TypeInfo)
	{
		m_TypeInfo = _TypeInfo;
	}

	template<typename TYPE>
	void TypeSetting()
	{
		m_TypeInfo = &typeid(TYPE);
	}

public:
	GameRTTI();
	virtual ~GameRTTI();
};

