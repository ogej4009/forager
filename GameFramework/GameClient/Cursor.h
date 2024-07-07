#pragma once
#include <LogicCom.h>
#include <GameMath.h>


class Cursor : public LogicCom
{
public:
	static void FootPrint(LogicCom* _Parent);
	static void g_EnterEvent(GameCol* _This, GameCol* _Other);
	void EnterEvent(GameCol* _This, GameCol* _Other);

public:
	void Init() override;
	void Update() override;
	void DebugRender() override;

public:
	Cursor();
	~Cursor();
};