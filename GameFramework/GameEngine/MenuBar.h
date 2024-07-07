#pragma once
#include "LogicCom.h"
#include "GameSprRender.h"
#include "GameCol.h"
#include "Inventory.h"


class MenuBar : public LogicCom
{
private:
	S_Ptr<Inventory> m_Inven;
	S_Ptr<GameSprRender> m_Render;
	S_Ptr<GameCol> m_Col;
	bool m_bKey;

public:
	static void FootPrint(LogicCom* _Parent);
	static void g_EnterEvent(GameCol* _This, GameCol* _Other);
	void EnterEvent(GameCol* _This, GameCol* _Other);

public:
	void Init() override;
	void Update() override;
	void DebugRender() override;

public:
	static void Load();

public:
	MenuBar();
	~MenuBar();
};