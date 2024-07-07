#pragma once
#include "GameDevice.h"
#include "GameShader.h"
#include "GameTexture.h"
#include <GameRes.h>

class GameSprite : public GameRes<GameSprite>
{
public:
	static S_Ptr<GameSprite> Create(const GameString& _TexPath, size_t _W, size_t _H)
	{
		GameString Name = _TexPath.PathData().ArrFullFile;
		GameSprite* NewRes = CreateRes(Name);
		NewRes->CreateSprite(Name, _W, _H);
		return NewRes;
	}

	static S_Ptr<GameSprite> Create(const GameString& _SpriteName, const GameString& _TexName, size_t _W, size_t _H)
	{
		GameSprite* NewRes = CreateRes(_SpriteName);
		NewRes->CreateSprite(_TexName, _W, _H);
		return NewRes;
	}

private:
	S_Ptr<GameTexture> m_Tex;
	std::vector<CVector> m_CutPos;
	std::vector<std::vector<CVector>> m_CutPos2D;

public:
	S_Ptr<GameTexture> Tex()
	{
		return m_Tex;
	}

	CVector CutData(size_t _Index)
	{
		if (_Index < 0)
		{
			CodeEmbeddedErrorDetection;
		}

		if (_Index >= m_CutPos.size())
		{
			CodeEmbeddedErrorDetection;
		}

		return m_CutPos[_Index];
	}

public:
	bool CreateSprite(const GameString& _TexName, size_t _W, size_t _H);

public:
	GameSprite();
	~GameSprite();
};

