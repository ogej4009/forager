#pragma once
#include <LogicCom.h>
#include <RenderTileBase.h>
#include <GameSprRender.h>

class RenderTileBase;
class Item;
class Inventory;
class GameCol;
class GameAni;
class Hero : public LogicCom
{
public:
	static bool g_IsCol;

private:
	GameString m_StateName;
	S_Ptr<GameCol> m_Col;
	S_Ptr<GameCol> m_Col2;
	float m_Speed;
	S_Ptr<GameAni> m_Ani;
	S_Ptr<GameSprRender> m_Render;
	S_Ptr<GameSprRender> m_RenderEQ;
	bool m_IsIdle;
	S_Ptr<Item> m_Item;

public:
	static void FootPrint(LogicCom* _Parent);
	static void g_EnterEvent(GameCol* _This, GameCol* _Other);
	void EnterEvent(GameCol* _This, GameCol* _Other);

public:
	bool IsState(GameString _StateName);
	void StateChange(GameString _StateName);

public:
	void Init() override;
	void Update() override;
	void DebugRender() override;

public:
	void Walk();
	void Idle();

public:
	Hero();
	~Hero();
};