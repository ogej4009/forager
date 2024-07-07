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
	// ���Ű�� ���ȴٸ� true
	// �ϳ��� �ȴ��ȴٸ� false

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
	// Ű�� üũ�غ���
	// ���ȴ�.
	if (true == AllKeyCheck())
	{
		// ���������ӱ��� Ű�� �������� ����.
		// �������� Ű�� �������� �����ϴ�.
		if (true == m_bRelease)
		{
			// Ű�� ������ �Ѽ���
			m_bUp = false;
			// Ű�� ���� �Ѽ���
			m_bDown = true;
			// Ű�� ��� ������ �ִ�.
			m_bPress = true;
			// Ű�� ��� ������ �ִ�.
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
	// Ű�� üũ�غ��� �ȴ�����.
	else
	{
		// ���� �����ӱ����� �����־���.
		if (true == m_bDown || true == m_bPress)
		{
			m_bUp = true;
			m_bDown = false;
			m_bPress = false;
			m_bRelease = true;
		}
		// ���������ӿ��� Ű�� ó������ ��������.
		// �׷��� Ű�� �������ٴ� üũ�� �������� ������ ���̱� ������.
		else if (true == m_bUp)
		{
			m_bUp = false;
			m_bDown = false;
			m_bPress = false;
			m_bRelease = true;
		}
	}

	// �� �����Ӹ��� Ű�� üũ�ؼ� 
	// ���¸� �������ش�.
	// ���� ���ȴ�.
	// ���� �������ִ�.
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