#pragma once
#include "LogicCom.h"
#include <GameMath.h>
#include "Item.h"


class Item;
class Inventory : public LogicCom
{
public:
	CVector m_ItemPos;
	S_Ptr<Item> m_Item;
	static S_Ptr<Item> m_Inven[8][4];
	S_Ptr<GameSprRender> m_Render;
	S_Ptr<GameSprRender> ITEMRENDER[8][4];
	S_Ptr<GameSprRender> XRENDER[8][4];
	S_Ptr<GameSprRender> COUNTRNEDER1[8][4];
	S_Ptr<GameSprRender> COUNTRNEDER2[8][4];
	static int SlotX;
	static int SlotY;

public:
	static void g_EnterEvent(GameCol* _This, GameCol* _Other);
	void EnterEvent(GameCol* _This, GameCol* _Other);

public:
	void Init() override;
	void Update() override;
	void DebugRender() override;

public:
	static void AddInven(int _x, int _y, S_Ptr<Item> _item)
	{
		if (m_Inven[_x][_y] != nullptr)
		{
			return;
		}

		//m_Inven
		SlotX = _x;
		SlotY = _y;

		m_Inven[SlotX][SlotY] = _item;
	}

public:
	static void Load();

public:
	Inventory();
	~Inventory();
};

