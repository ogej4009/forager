
#pragma once
#include "GameDevice.h"
#include <GameRes.h>

class GameBlend : public GameRes<GameBlend>
{
public:
	static S_Ptr<GameBlend> Create(const GameString& _Name, const D3D11_BLEND_DESC& _Desc)
	{
		GameBlend* NewRes = CreateRes(_Name);
		NewRes->Create(_Desc);
		return NewRes;
	}

private:
	D3D11_BLEND_DESC m_Desc;
	ID3D11BlendState* m_pBlend;

public:
	bool Create(const D3D11_BLEND_DESC& _Desc);
	void Setting();

public:
	GameBlend();
	~GameBlend();
};

