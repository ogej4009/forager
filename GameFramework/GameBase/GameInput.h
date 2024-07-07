#pragma once
#include <Windows.h>
#include <map>
#include <vector>
#include <string> 
#include "GameMacro.h"

class GameInput
{
private:
	class GameInputStatic
	{
	public:
		~GameInputStatic();
	};
	friend GameInputStatic;
	static GameInputStatic m_Inst;

private:
	class GameKey
	{
		friend GameInput;

	private:
		bool m_bUp;
		bool m_bDown;
		bool m_bPress;
		bool m_bRelease;

		std::vector<int> m_KeyVec;

	public:
		void Update();
		bool AllKeyCheck();

	public:
		void PushKey(int _Value)
		{
			m_KeyVec.push_back(_Value);
		}

	public:
		GameKey();
		~GameKey() {}
	};

private:
	static std::map<std::wstring, GameKey*> m_AllKey;
	static GameKey* CurCreateKey;

private:

	static GameKey* FindKey(const wchar_t* _Name);
	static bool IsKey(const wchar_t* _Name);

public:
	static void Update();

public:
	template<typename ...REST>
	static bool CreateKey(const wchar_t* _Name, REST... _Value)
	{
		if (true == IsKey(_Name))
		{
			return false;
		}

		CurCreateKey = new GameKey();

		PushKey(_Value ...);
		m_AllKey.insert(std::map<std::wstring, GameKey*>::value_type(_Name, CurCreateKey));
		return true;
	}

private:
	template<typename ...REST>
	static void PushKey(int _PushValue, REST... _Value)
	{
		CurCreateKey->m_KeyVec.push_back(_PushValue);
		PushKey(_Value ...);
	}

	static void PushKey()
	{
		// CurCreateKey = nullptr;
	}

public:
	static bool Press(const wchar_t* _Name);
	static bool Down(const wchar_t* _Name);
	static bool Up(const wchar_t* _Name);
	static bool Release(const wchar_t* _Name);

private:
	GameInput();
	~GameInput();
};

