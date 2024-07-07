#include "DropItem.h"

#include "GameActor.h"
#include <GameDirectory.h>
#include "GameTexture.h"
#include "GameSprite.h"
#include "GameCol.h"
#include "Inventory.h"
#include "RenderMisc.h"
#include "RenderTree.h"
#include "LogicData.h"

DropItem::DropItem() {}
DropItem::~DropItem() {}

void DropItem::Load()
{
	// 필드에 있는 아이템 입니다. 
	GameDirectory m_Dir;
	m_Dir.MoveParent(L"GameFramework");
	m_Dir.Move(L"Res");
	m_Dir.Move(L"Tex");
	GameTexture::Load(m_Dir.CreateGameFilePath(L"StoneDrop.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"StoneDrop.png"), 15, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"FossilDrop.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"FossilDrop.png"), 20, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"GoldOreDrop.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"GoldOreDrop.png"), 20, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"IronDrop.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"IronDrop.png"), 20, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"WoodDrop.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"WoodDrop.png"), 20, 1);
}

void DropItem::Init()
{

	m_Col = AddCom<GameCol>(GameCol::COLTYPE::OBBRECT, (UINT)COL_ORDER::CO_DROPITEM);
	m_Col->AddEnterEvent(this, &DropItem::EnterEvent);

	Trans()->LSCALE({ 0.5f,0.5f,1.0f });
	Trans()->LPOS({ -1000.0f,0.0f,0.0f });

	m_Item = AddCom<Item>();

	Off();

}

void DropItem::Update()
{

	if (ROBJ == TILEOBJ::T_OBJ)
	{
		//CVEC4 m_Pos = DROPPOS;
		std::list<S_Ptr<GameActor>>::iterator ACTORITER = RenderMisc::g_DropItemObjList.begin();
		std::list<S_Ptr<GameActor>>::iterator ACTORITEREND = RenderMisc::g_DropItemObjList.end();

		int i = 0;

		for (; ACTORITER != ACTORITEREND; ++ACTORITER)
		{
			if (i == LISTCOUNT)
			{
				if ((*ACTORITER)->IsDeath() == true)
				{
					On();
					Trans()->LPOS(DROPPOS);
				}
			}

			++i;
		}
	}
	else if (ROBJ == TILEOBJ::T_TREE)
	{
		std::list<S_Ptr<GameActor>>::iterator TACTORITER = RenderTree::g_DropItemObjList.begin();
		std::list<S_Ptr<GameActor>>::iterator TACTORITEREND = RenderTree::g_DropItemObjList.end();

		int i = 0;

		for (; TACTORITER != TACTORITEREND; ++TACTORITER)
		{
			if (i == LISTCOUNT)
			{
				if ((*TACTORITER)->IsDeath() == true)
				{
					On();
					Trans()->LPOS(DROPPOS);
				}
			}

			++i;
		}
	}
}

void DropItem::DebugRender()
{
}

void DropItem::SetDropItem(int _Code)
{

	for (auto& DROPITEM : m_Item->ItemList)
	{
		if (DROPITEM->ItemCode == _Code)
		{
			m_Render = AddCom<GameSprRender>((UINT)RENDER_ORDER::RO_DROPITEM);
			ANI = AddCom<GameAni>();
			ANI->CreateAni(DROPITEM->AniName, DROPITEM->DropPng, 0, DROPITEM->Frame, DROPITEM->AniTime, true);
			ANI->ChangeAni(DROPITEM->AniName);
			m_Render->Sprite(DROPITEM->DropPng);
			m_Item = DROPITEM;

			return;

		}
	}
}

void DropItem::SetItem(const GameString& _Str, int _Idx)
{
	// ObjRender의 아이템 이미지 인덱스에 맞는 아이템에 맞게 DropItem을 가지고 있다.
	GameString Rock = L"Rock.png";
	GameString Tree = L"Tree.png";
	if (Rock == _Str)
	{
		if (0 == _Idx || 1 == _Idx)
		{
			SetDropItem(0);
		}
		else if (2 == _Idx || 3 == _Idx)
		{
			SetDropItem(1);
		}
		else if (4 == _Idx || 5 == _Idx)
		{
			SetDropItem(2);
		}
		else if (6 == _Idx || 7 == _Idx)
		{
			SetDropItem(3);
		}
	}
	else if (Tree == _Str)
	{
		SetDropItem(4);
	}
}

void DropItem::g_EnterEvent(GameCol* _This, GameCol* _Other)
{

}

void DropItem::EnterEvent(GameCol* _This, GameCol* _Other)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (Inventory::m_Inven[i][j] == nullptr && m_Item->ItemCount == 0)
			{
				Inventory::AddInven(i, j, m_Item);
				++Inventory::m_Inven[i][j]->ItemCount;

				_This->Actor()->Death();

				return;

			}
			else if (Inventory::m_Inven[i][j] != nullptr && Inventory::m_Inven[i][j]->ItemCode == m_Item->ItemCode)
			{
				if (Inventory::m_Inven[i][j]->ItemCount < 20)
				{
					++Inventory::m_Inven[i][j]->ItemCount;

					_This->Actor()->Death();
				}
				return;

			}
		}
	}
}