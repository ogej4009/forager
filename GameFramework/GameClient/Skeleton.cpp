#include "Skeleton.h"
#include <LogicData.h>

Skeleton::Skeleton() {}
Skeleton::~Skeleton() {}

void Skeleton::Init()
{
	m_Render = AddCom<GameSprRender>((UINT)RENDER_ORDER::RO_MONSTER);
	m_Ani = AddCom<GameAni>();
	m_Ani->CreateAni(L"SkeletonIdle", L"SkeletonIdle.png", 0, 5, 0.07f, true);
	m_Ani->CreateAni(L"SkeletonWalk", L"SkeletonWalk.png", 0, 5, 0.07f, true);
	m_Ani->CreateAni(L"SkeletonUnburrow", L"SkeletonUnburrow.png", 0, 12, 0.07f, true);
	m_Ani->ChangeAni(L"SkeletonIdle");
	m_Render->Sprite(L"SkeletonIdle.png");
	m_Render->Sprite(L"SkeletonWalk.png");
	m_Render->Sprite(L"SkeletonUnburrow.png");
	m_Col = AddCom<GameCol>(GameCol::COLTYPE::OBBRECT, (UINT)COL_ORDER::CO_MONSTER);
}

void Skeleton::Update()
{
}

void Skeleton::DebugRender()
{
}