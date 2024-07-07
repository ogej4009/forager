
#pragma once
#include <LogicCom.h>
#include <GameSprRender.h>
#include <GameAni.h>
#include <GameCol.h>

class Slime : public LogicCom
{
private:
	S_Ptr<GameSprRender> m_Render;
	S_Ptr<GameAni> m_Ani;
	S_Ptr<GameCol> m_Col;

public:
	void Init() override;
	void Update() override;
	void DebugRender() override;

public:
	Slime();
	~Slime();
};