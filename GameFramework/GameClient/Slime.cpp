#include "Slime.h"
#include <LogicData.h>


Slime::Slime() {}
Slime::~Slime() {}

void Slime::Init()
{
	m_Render = AddCom<GameSprRender>((UINT)RENDER_ORDER::RO_MONSTER);
	m_Ani = AddCom<GameAni>();
	m_Ani->CreateAni(L"Slime", L"Slime.png", 0, 4, 0.07f, true);
	m_Ani->ChangeAni(L"Slime");
	m_Render->Sprite(L"Slime.png");
	m_Col = AddCom<GameCol>(GameCol::COLTYPE::OBBRECT, (UINT)RENDER_ORDER::RO_MONSTER);
}

void Slime::Update()
{
}

void Slime::DebugRender()
{
}