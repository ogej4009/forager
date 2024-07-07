#pragma once

#include "LogicCom.h"
#include "GameActor.h"
#include "GameSprRender.h"
#include "GameCol.h"
#include <list>

class Item : public LogicCom
{
public:
	int ItemCode; // 아이템 코드
	GameString InvenPng; // 인벤토리 내 이미지 파일 이름
	GameString DropPng; // 월드 내 Drop 상태의 이미지 파일 이름
	GameString AniName;
	int Frame; // DorpItem 상태일 때 애니 프레임
	float AniTime; // DorpItem 상태일 때 애니 프레임
	int ItemCount; // 인벤토리 내 겹쳐진 갯수

public:
	std::list<S_Ptr<Item>> ItemList; // 게임 내 모든 아이템 리스트

public:
	void Init() override;
	void Update() override;
	void DebugRender() override;

public:
	static void Load();

public:
	void AddItemList(int _Code, const GameString& _Inven, const GameString& _Drop, const GameString& _Ani, int _Frame, float _time)
	{
		Item* NewItem = new Item;
		NewItem->ItemCode = _Code;
		NewItem->InvenPng = _Inven;
		NewItem->DropPng = _Drop;
		NewItem->AniName = _Ani;
		NewItem->Frame = _Frame;
		NewItem->AniTime = _time;
		ItemList.push_back(NewItem);
	}

public:
	Item();
	~Item();
};

