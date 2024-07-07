#pragma once
#include "GameString.h"

class GameName
{
private:
	GameString m_Name;

public:
	std::wstring GetWStrName()
	{
		return m_Name;
	}

public:
	GameString GetCGStrName()
	{
		return m_Name;
	}

public:
	const wchar_t* GetCWTName()
	{
		return m_Name;
	}

public:
	void SetCWTName(const wchar_t* _Name)
	{
		m_Name = _Name;
	}

	void SetWStrName(std::wstring& _Name)
	{
		m_Name = _Name;
	}

	void SetCGStrName(const GameString& _Name)
	{
		m_Name = _Name;
	}

public:
	GameName() {}
	~GameName() {}
};


