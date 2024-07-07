#include "Inventory.h"

#include <GameDirectory.h>
#include "GameTexture.h"
#include "GameSprite.h"
#include "GameCol.h"

#include <LogicData.h>
#include "GameSprRender.h"
#include <GameInput.h>


//std::list<Item*> CInven::InvenList;
S_Ptr<Item> Inventory::m_Inven[8][4];
int Inventory::SlotX;
int Inventory::SlotY;

Inventory::Inventory() {}
Inventory::~Inventory() {}

void Inventory::Load()
{
	GameDirectory m_Dir;
	m_Dir.MoveParent(L"GameFramework");
	m_Dir.Move(L"Res");
	m_Dir.Move(L"Tex");

	GameTexture::Load(m_Dir.CreateGameFilePath(L"InventorySlotTopLeft.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"InventorySlotTopLeft.png"), 3, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"FontUI.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"FontUI.png"), 12, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"TextBox.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"TextBox.png"), 6, 1);

	// 인벤토리에 있는 아이템 이미지
	GameTexture::Load(m_Dir.CreateGameFilePath(L"sprStone.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"sprStone.png"), 1, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"sprFossil.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"sprFossil.png"), 1, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"sprGoldOre.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"sprGoldOre.png"), 1, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"sprIronOre.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"sprIronOre.png"), 1, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"sprWood.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"sprWood.png"), 1, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"dummy.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"dummy.png"), 1, 1);

}

void Inventory::g_EnterEvent(GameCol* _This, GameCol* _Other)
{
	if (true == GameInput::Press(L"LEFTMOUSE"))
	{
		int a = 0;
	}
}

void Inventory::EnterEvent(GameCol* _This, GameCol* _Other)
{
}

void Inventory::Init()
{
	GameInput::CreateKey(L"LEFTMOUSE", VK_LBUTTON);

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{

			m_ItemPos.x = -3.5f + j;
			m_ItemPos.y = 2.0f - i;
			m_ItemPos.z = -2;

			S_Ptr<GameCol> m_Col = AddCom<GameCol>(GameCol::COLTYPE::OBBRECT, (UINT)COL_ORDER::CO_ITEM);
			m_Col->LSCALE({ 0.5f,0.5f,1.0f });
			m_Col->LPOS(m_ItemPos);

			m_Render = AddCom<GameSprRender>((UINT)RENDER_ORDER::RO_UI);
			m_Render->LPOS(m_ItemPos); // 맨 첫번째 위치 : -5, -1
			m_Render->Sprite(L"InventorySlotTopLeft.png");
			m_ItemPos.z = -3;
			ITEMRENDER[i][j] = AddCom<GameSprRender>((UINT)RENDER_ORDER::RO_UI);
			ITEMRENDER[i][j]->LSCALE({ 0.8f,0.8f,1.0f });
			ITEMRENDER[i][j]->Sprite(L"dummy.png");
			ITEMRENDER[i][j]->LPOS(m_ItemPos);
			//m_Inven[i][j]->Trans()->LPOS(m_ItemPos);

			// X
			XRENDER[i][j] = AddCom<GameSprRender>((UINT)RENDER_ORDER::RO_UI);
			XRENDER[i][j]->LSCALE({ 0.3f,0.3f,1.0f });
			XRENDER[i][j]->Sprite(L"FontUI.png");
			XRENDER[i][j]->Index(11);
			XRENDER[i][j]->LPOS({ m_ItemPos.x, m_ItemPos.y - 0.2f,m_ItemPos.z });

			// ITemCount첫번째자리
			COUNTRNEDER1[i][j] = AddCom<GameSprRender>((UINT)RENDER_ORDER::RO_UI);
			COUNTRNEDER1[i][j]->LSCALE({ 0.3f,0.3f,1.0f });
			COUNTRNEDER1[i][j]->Sprite(L"FontUI.png");
			COUNTRNEDER1[i][j]->Index(11);
			COUNTRNEDER1[i][j]->LPOS({ m_ItemPos.x + 0.17f, m_ItemPos.y - 0.2f,m_ItemPos.z });
			// ITemCount두번째자리
			COUNTRNEDER2[i][j] = AddCom<GameSprRender>((UINT)RENDER_ORDER::RO_UI);
			COUNTRNEDER2[i][j]->LSCALE({ 0.3f,0.3f,1.0f });
			COUNTRNEDER2[i][j]->Sprite(L"FontUI.png");
			COUNTRNEDER2[i][j]->Index(11);
			COUNTRNEDER2[i][j]->LPOS({ m_ItemPos.x + 0.34f, m_ItemPos.y - 0.2f,m_ItemPos.z });
		}

	}

	// InvenList 미리 셋팅

}

void Inventory::Update()
{
	// 인벤리스트의 변동에 따라 바뀐다.
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			m_ItemPos.x = -3.5f + j;
			m_ItemPos.y = 2.0f - i;
			m_ItemPos.z = -2;

			if (m_Inven[i][j] != nullptr)
			{
				ITEMRENDER[i][j]->Sprite(m_Inven[i][j]->InvenPng);
				ITEMRENDER[i][j]->LPOS(m_ItemPos);

				if (m_Inven[i][j]->ItemCount == 0)
				{
					XRENDER[i][j]->Index(11);
					COUNTRNEDER1[i][j]->Index(11);
					COUNTRNEDER2[i][j]->Index(11);
				}
				else if (m_Inven[i][j]->ItemCount > 0)
				{

					for (int k = 0; k < 20; ++k)
					{
						int num = k + 1;

						if (m_Inven[i][j]->ItemCount == num)
						{

							if (num < 10)
							{
								XRENDER[i][j]->Index(10);
								COUNTRNEDER1[i][j]->Index(0);
								COUNTRNEDER2[i][j]->Index(num);
							}
							else if (num < 20)
							{
								XRENDER[i][j]->Index(10);
								COUNTRNEDER1[i][j]->Index(1);
								COUNTRNEDER2[i][j]->Index(num - 10);
							}
							else if (num == 20)
							{
								XRENDER[i][j]->Index(10);
								COUNTRNEDER1[i][j]->Index(2);
								COUNTRNEDER2[i][j]->Index(0);
							}

							break;
						}
					}



				}


			}



		}

	}
}

void Inventory::DebugRender()
{
}

