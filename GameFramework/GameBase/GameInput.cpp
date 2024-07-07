#include "GameInput.h"

std::map<std::wstring, GameInput::GameKey*> GameInput::m_AllKey;
GameInput::GameKey* GameInput::CurCreateKey;
GameInput::GameInputStatic GameInput::m_Inst;

GameInput::GameInputStatic::~GameInputStatic()
{
	std::map<std::wstring, GameInput::GameKey*>::iterator StartIter = GameInput::m_AllKey.begin();
	std::map<std::wstring, GameInput::GameKey*>::iterator EndIter = GameInput::m_AllKey.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}

	m_AllKey.clear();
}

GameInput::GameInput() {}
GameInput::~GameInput() {}

GameInput::GameKey::GameKey()
	: m_bUp(false)
	, m_bDown(false)
	, m_bPress(false)
	, m_bRelease(true)
{
}

bool GameInput::GameKey::AllKeyCheck()
{
	// 모든키가 눌렸다면 true
	// 하나라도 안눌렸다면 false

	for (size_t i = 0; i < m_KeyVec.size(); i++)
	{

		if (0 == GetAsyncKeyState(m_KeyVec[i]))
		{
			return false;
		}
	}

	return true;
}

void GameInput::GameKey::Update()
{
	// 키를 체크해보니
	// 눌렸다.
	if (true == AllKeyCheck())
	{
		// 이전프레임까지 키가 눌린적이 없다.
		// 이전까지 키가 눌린적이 없습니다.
		if (true == m_bRelease)
		{
			// 키가 떼어진 한순간
			m_bUp = false;
			// 키가 눌린 한순간
			m_bDown = true;
			// 키가 계속 눌리고 있다.
			m_bPress = true;
			// 키가 계속 떼어져 있다.
			m_bRelease = false;
		}
		else if (false == m_bRelease)
		{
			m_bUp = false;
			m_bDown = false;
			m_bPress = true;
			m_bRelease = false;
		}
	}
	// 키를 체크해보니 안눌렀다.
	else
	{
		// 이전 프레임까지는 눌려있었다.
		if (true == m_bDown || true == m_bPress)
		{
			m_bUp = true;
			m_bDown = false;
			m_bPress = false;
			m_bRelease = true;
		}
		// 이전프레임에서 키가 처음으로 떼어졌다.
		// 그런데 키가 떼어졌다는 체크는 한프레임 유지할 것이기 때문에.
		else if (true == m_bUp)
		{
			m_bUp = false;
			m_bDown = false;
			m_bPress = false;
			m_bRelease = true;
		}
	}

	// 매 프레임마다 키를 체크해서 
	// 상태를 설정해준다.
	// 내가 눌렸다.
	// 내가 떼어져있다.
}

GameInput::GameKey* GameInput::FindKey(const wchar_t* _Name)
{
	// std::wstring Test = _Name;
	std::map<std::wstring, GameKey*>::iterator Iter = m_AllKey.find(_Name);
	if (Iter == m_AllKey.end())
	{
		return nullptr;
	}
	return Iter->second;
}

bool GameInput::IsKey(const wchar_t* _Name)
{
	if (m_AllKey.end() == m_AllKey.find(_Name))
	{
		return false;
	}

	return true;
}

void GameInput::Update()
{
	std::map<std::wstring, GameInput::GameKey*>::iterator StartIter = GameInput::m_AllKey.begin();
	std::map<std::wstring, GameInput::GameKey*>::iterator EndIter = GameInput::m_AllKey.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			StartIter->second->Update();
		}
	}
}

bool GameInput::Press(const wchar_t* _Name)
{
	GameKey* FKey = FindKey(_Name);
	if (nullptr == FKey)
	{
		CodeEmbeddedErrorDetection;
	}

	return FKey->m_bPress;
}

bool GameInput::Down(const wchar_t* _Name)
{
	GameKey* FKey = FindKey(_Name);
	if (nullptr == FKey)
	{
		CodeEmbeddedErrorDetection;
	}

	return FKey->m_bDown;

}

bool GameInput::Up(const wchar_t* _Name)
{
	GameKey* FKey = FindKey(_Name);
	if (nullptr == FKey)
	{
		CodeEmbeddedErrorDetection;
	}

	return FKey->m_bUp;
}

bool GameInput::Release(const wchar_t* _Name)
{
	GameKey* FKey = FindKey(_Name);
	if (nullptr == FKey)
	{
		CodeEmbeddedErrorDetection;
	}

	return FKey->m_bRelease;
}