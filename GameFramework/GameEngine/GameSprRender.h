#pragma once
#include "GameRender.h"
#include "GameSprite.h"

class GameSprRender : public GameRender
{
private:
	S_Ptr<GameSprite> m_Sprite;
	size_t m_Index;
	GameRenderData* RD;
	CVector m_Color;

public:
	void Color(CVector _Color)
	{
		m_Color = _Color;
	}

	void Index(size_t _Index);

	size_t Index()
	{
		return m_Index;
	}

public:
	void Sprite(const GameString& _Name);

	S_Ptr<GameSprite> Sprite()
	{
		return m_Sprite;
	}

public:
	void RenderUpdate(S_Ptr<GameCamera> _Cam) override;
	void Init(unsigned int _Order = 0) override;

public:
	GameSprRender();
	~GameSprRender();
};

