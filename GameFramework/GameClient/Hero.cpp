#include "Hero.h"
#include <LogicData.h>
#include <GameAni.h>
#include <GameInput.h>
#include <GameFrameDebug.h>
#include <GameCol.h>
#include <LogicData.h>
#include <GameDirectory.h>
#include <DropItem.h>
#include <Item.h>
#include <Inventory.h>
#include <DropItem.h>
#include "PlayScene.h"

bool Hero::g_IsCol;

Hero::Hero()
	: m_Speed(2.0f)
	, m_IsIdle(true)
{
}

Hero::~Hero()
{
}

void Hero::Init()
{
	GameInput::CreateKey(L"LMOVE", 'A');
	GameInput::CreateKey(L"RMOVE", 'D');
	GameInput::CreateKey(L"UMOVE", 'W');
	GameInput::CreateKey(L"DMOVE", 'S');
	GameInput::CreateKey(L"ATTACK", 'Q');

	m_Col = AddCom<GameCol>(GameCol::COLTYPE::OBBRECT, (UINT)COL_ORDER::CO_PLAYER);
	m_Col->AddEnterEvent(this, &Hero::EnterEvent);
	//m_Col->AddEnterEvent(&Hero::g_EnterEvent);
	m_Col2 = AddCom<GameCol>(GameCol::COLTYPE::OBBRECT, (UINT)COL_ORDER::CO_PLAYER_SUB);
	m_Col2->AddEnterEvent(this, &Hero::EnterEvent);

	m_Render = AddCom<GameSprRender>((UINT)RENDER_ORDER::RO_PLAYER);
	m_Ani = AddCom<GameAni>();
	m_Ani->CreateAni(L"Walk", L"PlayerWalk.png", 0, 6, 0.07f, true);
	m_Ani->CreateAni(L"Idle", L"PlayerIdle.png", 0, 5, 0.07f, true);

	m_Ani->AddStartEvent(L"Walk", 5, &Hero::FootPrint);
	m_Render->Sprite(L"PlayerWalk.png");
	m_Render->Sprite(L"PlayerIdle.png");

	m_RenderEQ = AddCom<GameSprRender>((UINT)RENDER_ORDER::RO_PLAYER);
	m_RenderEQ->Sprite(L"Pickaxe.png");

	//StateChange(L"Walk");
	StateChange(L"Idle");

	m_Item = AddCom<Item>();

}

void Hero::FootPrint(LogicCom* _Parent)
{
}

void Hero::g_EnterEvent(GameCol* _This, GameCol* _Other)
{
}

void Hero::EnterEvent(GameCol* _This, GameCol* _Other)
{
	if (_Other->GetOrder() == (UINT)COL_ORDER::CO_MONSTER)
	{
		//int a = 0;
	}

	if (_Other->GetOrder() == (UINT)COL_ORDER::CO_DROPITEM)
	{
		//int a = 0;
	}

	if (_Other->GetOrder() == (UINT)COL_ORDER::CO_MISC)
	{
		_Other->Actor()->Death();
	}
}

bool Hero::IsState(GameString _StateName)
{
	return m_StateName == _StateName;
}

void Hero::StateChange(GameString _StateName)
{
	m_StateName = _StateName;
	m_Ani->ChangeAni(_StateName);
}

void Hero::Walk()
{
	if (true == GameInput::Press(L"LMOVE"))
	{
		Trans()->ScaleXMinus();

		if (PlayScene::g_GroundTile->IsTile(Trans()->WPOS() + CVector::LEFT * GameTime::DeltaTime() * m_Speed - 0.5f))
		{
			Trans()->LMOVETOTIMESPEED(CVector::LEFT, m_Speed);
		}
	}

	else if (true == GameInput::Press(L"RMOVE"))
	{
		Trans()->ScaleXPlus();

		if (PlayScene::g_GroundTile->IsTile(Trans()->WPOS() + CVector::RIGHT * GameTime::DeltaTime() * m_Speed + 0.5f))
		{
			Trans()->LMOVETOTIMESPEED(CVector::RIGHT, m_Speed);
		}

	}
	else if (true == GameInput::Press(L"UMOVE"))
	{
		if (PlayScene::g_GroundTile->IsTile(Trans()->WPOS() + CVector::UP * GameTime::DeltaTime() * m_Speed))
		{
			Trans()->LMOVETOTIMESPEED(CVector::UP, m_Speed);
		}

	}
	else if (true == GameInput::Press(L"DMOVE"))
	{
		if (PlayScene::g_GroundTile->IsTile(Trans()->WPOS() + CVector::DOWN * GameTime::DeltaTime() * m_Speed - 0.5f))
		{
			Trans()->LMOVETOTIMESPEED(CVector::DOWN, m_Speed);
		}

	}

	else if (true == GameInput::Release(L"LMOVE")
		|| true == GameInput::Release(L"RMOVE")
		|| true == GameInput::Release(L"UMOVE")
		|| true == GameInput::Release(L"DMOVE"))
	{
		g_IsCol = false;
		StateChange(L"Idle");
	}
}


void Hero::Idle()
{
	if (true == GameInput::Press(L"LMOVE")
		|| true == GameInput::Press(L"RMOVE")
		|| true == GameInput::Press(L"UMOVE")
		|| true == GameInput::Press(L"DMOVE"))
	{
		StateChange(L"Walk");
	}
}


void Hero::Update()
{
	CVector EQPos;
	EQPos.x = m_Render->LPOS().x - 0.27f;
	EQPos.y = m_Render->LPOS().y - 0.05f;
	EQPos.z = m_Render->LPOS().z;
	m_RenderEQ->LPOS(EQPos);

	// UI가 켜져있을 땐 못 움직임
	if (PlayScene::g_IsUIOn == false)
	{
		if (IsState(L"Walk"))
		{
			Walk();
		}
		else if (IsState(L"Idle"))
		{
			Idle();
		}
	}

}

void Hero::DebugRender()
{
	//GameFrameDebug::Draw2DRect(Trans());
}
