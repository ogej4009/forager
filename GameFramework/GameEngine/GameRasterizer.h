#pragma once
#include "GameDevice.h"
#include <GameRes.h>


class GameRasterizer : public GameRes<GameRasterizer>
{
private:
	D3D11_RASTERIZER_DESC m_Desc;
	ID3D11RasterizerState* m_pRasterizer;

public:
	static S_Ptr<GameRasterizer> Create(const GameString& _Name, const D3D11_RASTERIZER_DESC& _Desc)
	{
		GameRasterizer* NewRes = CreateRes(_Name);
		NewRes->Create(_Desc);
		return NewRes;
	}

public:
	bool Create(const D3D11_RASTERIZER_DESC& _Desc);
	void Setting();

public:
	GameRasterizer();
	~GameRasterizer();

};

