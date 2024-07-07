#pragma once

#include "LogicCom.h"
#include "GameActor.h"
#include "GameSprRender.h"
#include "GameCol.h"
#include <list>

class Item : public LogicCom
{
public:
	int ItemCode; // ������ �ڵ�
	GameString InvenPng; // �κ��丮 �� �̹��� ���� �̸�
	GameString DropPng; // ���� �� Drop ������ �̹��� ���� �̸�
	GameString AniName;
	int Frame; // DorpItem ������ �� �ִ� ������
	float AniTime; // DorpItem ������ �� �ִ� ������
	int ItemCount; // �κ��丮 �� ������ ����

public:
	std::list<S_Ptr<Item>> ItemList; // ���� �� ��� ������ ����Ʈ

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

