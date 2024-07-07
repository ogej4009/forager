#include "GameSprRender.h"

#include "GameSampler.h"
#include "GameTexture.h"
#include "GameCamera.h"

GameSprRender::GameSprRender()
	: m_Index(0)
{
}

GameSprRender::~GameSprRender()
{
}

void GameSprRender::Init(unsigned int _Order)
{
	GameRender::Init(_Order);
	m_Color = CVector::WHITE;
	RD = CreateRenderData(L"RECT2D", L"SPRITE2D");
	RD->SMP(L"LSMP", L"LSMP");
	RD->SMP(L"PSMP", L"PSMP");
	RD->CB(L"CB_COLOR", m_Color, true);
}

void GameSprRender::Index(size_t _Index)
{
	m_Index = _Index;
}

void GameSprRender::Sprite(const GameString& _Name)
{
	m_Sprite = GameSprite::Find(_Name);

	if (nullptr == m_Sprite)
	{
		CodeEmbeddedErrorDetection;
	}

}

void GameSprRender::RenderUpdate(S_Ptr<GameCamera> _Cam)
{
	RD->TEX(L"TEX2D", m_Sprite->Tex());
	RD->CB(L"CB_CUT", m_Sprite->CutData(m_Index));
}

