#pragma once
#include "LogicCom.h"
#include "Item.h"
#include "GameSprRender.h"
#include "GameAni.h"
#include "GameActor.h"


enum TILEOBJ
{
	T_OBJ,
	T_TREE,
	T_MAX,
};

// 필드에 떨어진 아이템 입니다. 
class GameCol;
class DropItem : public LogicCom
{
private:
	S_Ptr<Item> m_Item;
	S_Ptr<GameSprRender> m_Render;
	S_Ptr<GameAni> ANI;
	S_Ptr<GameCol> m_Col;
	CVector DROPPOS;
	int LISTCOUNT;
	TILEOBJ ROBJ;

public:
	static void g_EnterEvent(GameCol* _This, GameCol* _Other);
	void EnterEvent(GameCol* _This, GameCol* _Other);

public:
	void Init() override;
	void Update() override;
	void DebugRender() override;

	int GetItemCode()
	{
		return m_Item->ItemCode;
	}

	void SetDropItem(int _Code);

	void SetItem(const GameString& _Str, int _Idx);

	void SetDropPos(CVector _Pos)
	{
		DROPPOS = _Pos;
	}

	void SetListCount(int _Count)
	{
		LISTCOUNT = _Count;
	}

	void SetROBJ(TILEOBJ _Obj)
	{
		ROBJ = _Obj;
	}

public:
	static void Load();

public:
	DropItem();
	~DropItem();
};

