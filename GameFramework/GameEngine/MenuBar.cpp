#include "MenuBar.h"

#include "Inventory.h"
#include "Item.h"
#include <GameDirectory.h>
#include <GameInput.h>
#include "GameFrameDebug.h"
#include "GameCol.h"
#include "LogicData.h"

MenuBar::MenuBar()
	: m_bKey(false)
{
}

MenuBar::~MenuBar()
{
}

void MenuBar::Load()
{
	GameDirectory m_Dir;
	m_Dir.MoveParent(L"GameFramework");
	m_Dir.Move(L"Res");
	m_Dir.Move(L"Tex");
	GameTexture::Load(m_Dir.CreateGameFilePath(L"MenuTabIcon.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"MenuTabIcon.png"), 5, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"MenuTabWindow.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"MenuTabWindow.png"), 5, 1);
}

void MenuBar::FootPrint(LogicCom* _Parent)
{
}

void MenuBar::g_EnterEvent(GameCol* _This, GameCol* _Other)
{
}

void MenuBar::EnterEvent(GameCol* _This, GameCol* _Other)
{
}

void MenuBar::Init()
{

	for (int i = 0; i < 5; ++i)
	{
		S_Ptr<GameSprRender> RENDER1 = AddCom<GameSprRender>((UINT)RENDER_ORDER::RO_UI);
		RENDER1->LPOS({ -2.0f + i,3.5f,-2.0f }); // 
		RENDER1->Sprite(L"MenuTabWindow.png");
		RENDER1->Index(i);
	}

	for (int i = 0; i < 5; ++i)
	{
		// 아이콘 기본상태는 반투명에다 작게한다.
		m_Render = AddCom<GameSprRender>((UINT)RENDER_ORDER::RO_UI);
		m_Render->LPOS({ -2.0f + i,3.5f,-2.0f }); // 
		m_Render->Sprite(L"MenuTabIcon.png");
		m_Render->Index(i);
		m_Col = AddCom<GameCol>(GameCol::COLTYPE::OBBRECT, (UINT)COL_ORDER::CO_UI);
		m_Col->LSCALE({ 0.8f,0.8f,0.8f });
		m_Col->LPOS({ -2.0f + i,3.5f,-2.0f });
	}

	// 인벤토리
	{
		m_Inven = AddCom<Inventory>();
	}
}

void MenuBar::Update()
{
}

void MenuBar::DebugRender()
{
}