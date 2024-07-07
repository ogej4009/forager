#include "Boar.h"
#include <LogicData.h>


Boar::Boar()
{
}

Boar::~Boar()
{
}

void Boar::Init()
{
	m_Render = AddCom<GameSprRender>((UINT)RENDER_ORDER::RO_MONSTER);
	m_Ani = AddCom<GameAni>();
	m_Ani->CreateAni(L"BoarIdle", L"BoarIdle.png", 0, 4, 0.07f, true);
	m_Ani->CreateAni(L"BoarWalk", L"BoarWalk.png", 0, 6, 0.07f, true);
	m_Ani->ChangeAni(L"BoarIdle");
	m_Render->Sprite(L"BoarIdle.png");
	m_Render->Sprite(L"BoarWalk.png");
	m_Col = AddCom<GameCol>(GameCol::COLTYPE::OBBRECT, (UINT)COL_ORDER::CO_MONSTER);
}

void Boar::Update()
{
}

void Boar::DebugRender()
{
}