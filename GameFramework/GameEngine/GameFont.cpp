#include "GameFont.h"
#include "GameDevice.h"


IFW1Factory* GameFont::m_pFontFactory = nullptr;

GameFont::GameFont() : m_pFontWrapper(nullptr)// , m_pFontFactory(nullptr)
{
}

GameFont::~GameFont()
{
	if (nullptr != m_pFontFactory)
	{
		m_pFontFactory->Release();
	}

	if (nullptr != m_pFontWrapper)
	{
		m_pFontWrapper->Release();
	}
}


bool GameFont::CreateGameFont(const GameString& _FontName)
{
	if (nullptr == m_pFontFactory)
	{
		if (S_OK != FW1CreateFactory(FW1_VERSION, &m_pFontFactory))
		{
			CodeEmbeddedErrorDetection;
			return false;
		}
	}

	HRESULT RE = m_pFontFactory->CreateFontWrapper(GameDevice::MainDevice(), _FontName, &m_pFontWrapper);

	if (S_OK != RE)
	{
		CodeEmbeddedErrorDetection;
		return false;
	}

	return true;
}

void GameFont::DrawUI(const GameString& _Text, float _Size, CVector _Pos, CVector _Color, FW1_TEXT_FLAG _Flag /*= FW1_TOP*/) {

	if (nullptr == m_pFontWrapper)
	{
		CodeEmbeddedErrorDetection;
		return;
	}

	// m_pFontWrapper->DrawGeometry()

	// 무조건 스크린 좌표계이다.
	m_pFontWrapper->DrawString(GameDevice::MainContext(), _Text, _Size, _Pos.x, _Pos.y, _Color.ColorToUint(), _Flag);
}