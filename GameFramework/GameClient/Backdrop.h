#pragma once
#include <LogicCom.h>
#include <GameScene.h>
#include <GameSprRender.h>

class GameSprRender;
class Backdrop : public LogicCom
{
private:
	S_Ptr<GameSprRender> m_Render;
	CVector m_Pos;

public:
	void Init() override;
	void Update() override;
	void DebugRender() override;

public:
	void SetPos(CVector _Pos)
	{
		m_Pos = _Pos;
	}

	void SetSprite(GameString Str)
	{
		m_Render->Sprite(Str);
	}

public:
	Backdrop();
	~Backdrop();
};