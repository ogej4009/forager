#include "GameFrameDebug.h"

#include "GameActor.h"
#include "GameScene.h"
#include "GameCamera.h"
#include "GameFont.h"


size_t GameFrameDebug::m_DrawFontCount = 0;
size_t GameFrameDebug::m_DrawCount = 0;

CTransformData	GameFrameDebug::m_DebugTransData;
S_Ptr<GameRenderData> GameFrameDebug::RectRenderData;

std::vector<GameFrameDebug::DEBUGDRAWINFO> GameFrameDebug::m_Info;
std::vector<GameFrameDebug::DEBUGFONTINFO> GameFrameDebug::m_FontInfo;

CVector GameFrameDebug::m_DebugColor = CVector::WHITE;

GameFrameDebug::GameFrameDebug() {}
GameFrameDebug::~GameFrameDebug() {}

void GameFrameDebug::Init()
{
	m_DrawCount = 0;
	m_Info.resize(1000);
	m_FontInfo.resize(1000);

	RectRenderData = new GameRenderData(L"DEBUG_RECT2D", L"DEBUG2D");// DEBUG3D 2DRECT
	RectRenderData->m_pData = &m_DebugTransData;
	RectRenderData->MaterialInit();
	RectRenderData->m_DrawMode = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
	RectRenderData->CB(L"CB_DEBUG_COLOR", m_DebugColor, true);// DEBUGCOLOR
}

void GameFrameDebug::DebugRender()
{
	for (size_t i = 0; i < m_DrawCount; i++)
	{
		m_DebugTransData.W = m_Info[i].m_Trans->CREFWW();
		m_DebugTransData.W.ArrVec[3].z -= 0.1F;
		m_DebugTransData.V = m_Info[i].m_Cam->MatView();
		m_DebugTransData.P = m_Info[i].m_Cam->MatProj();
		m_DebugTransData.WV = m_DebugTransData.W * m_DebugTransData.V;
		m_DebugTransData.VP = m_Info[i].m_Cam->MatViewProj();
		m_DebugTransData.WVP = m_DebugTransData.W * m_DebugTransData.V * m_DebugTransData.P;
		m_DebugTransData.AllTP();
		m_DebugColor = m_Info[i].Color;

		m_Info[i].RD->Render();
	}

	m_DrawCount = 0;

	S_Ptr<GameFont> Font = GameFont::Find(L"±¼¸²");

	if (nullptr == Font)
	{
		CodeEmbeddedErrorDetection;
	}

	for (size_t i = 0; i < m_DrawFontCount; i++)
	{
		Font->DrawUI(m_FontInfo[i]._Text, m_FontInfo[i]._Size, m_FontInfo[i]._Pos, m_FontInfo[i]._Color);
	}
	m_DrawFontCount = 0;

	GameDevice::MainContext()->VSSetShader(nullptr, nullptr, 0);
	GameDevice::MainContext()->PSSetShader(nullptr, nullptr, 0);
	GameDevice::MainContext()->DSSetShader(nullptr, nullptr, 0);
	GameDevice::MainContext()->HSSetShader(nullptr, nullptr, 0);
	GameDevice::MainContext()->GSSetShader(nullptr, nullptr, 0);

}

void GameFrameDebug::Draw2DRect(GameTransform* _Trans, CVector _Color)
{
	Draw2DRect(GameScene::CurScene()->RENDERMGR.MainCam(), _Trans, _Color);
}

void GameFrameDebug::Draw2DRect(GameCamera* _Cam, GameTransform* _Trans, CVector _Color)
{
	m_Info[m_DrawCount].m_Trans = _Trans;
	m_Info[m_DrawCount].m_Cam = _Cam;
	m_Info[m_DrawCount].Color = _Color;
	m_Info[m_DrawCount].RD = RectRenderData;
	++m_DrawCount;
}

void GameFrameDebug::Draw2DFont(const GameString& _Text, const float& _Size, const CVector& _Pos, const CVector& _Color)
{
	m_FontInfo[m_DrawFontCount]._Text = _Text;
	m_FontInfo[m_DrawFontCount]._Size = _Size;
	m_FontInfo[m_DrawFontCount]._Pos = _Pos;
	m_FontInfo[m_DrawFontCount]._Color = _Color;
	++m_DrawFontCount;

}