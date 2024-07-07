#include "Backdrop.h"
#include <GameSprRender.h>
#include <GameDirectory.h>
#include <GameTime.h>

Backdrop::Backdrop()
{
}

Backdrop::~Backdrop()
{
}

void Backdrop::Init()
{
	m_Render = AddCom<GameSprRender>();
	//m_Render->Sprite(L"MainBackground.png");
}

void Backdrop::Update()
{
	m_Pos.x += 100.f * GameTime::DeltaTime();

	if (m_Pos.x >= 1204.0f)
	{
		m_Pos.x -= 1204.0f * 2;
	}

	m_Render->Trans()->LPOS(m_Pos);

}

void Backdrop::DebugRender()
{
}