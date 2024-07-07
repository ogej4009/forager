#pragma once
#include <GameRes.h>
#include "GameDevice.h"


class GameDepthstencil : public GameRes<GameDepthstencil>
{
private:
	D3D11_DEPTH_STENCIL_DESC m_Decs;
	ID3D11DepthStencilState* m_pDSS;

public:
	static S_Ptr<GameDepthstencil> Create(const GameString& _Name, const D3D11_DEPTH_STENCIL_DESC& _Decs)
	{
		GameDepthstencil* NewRes = CreateRes(_Name);
		NewRes->Create(_Decs);
		return NewRes;
	}

public:
	bool Create(const D3D11_DEPTH_STENCIL_DESC& _Decs);
	void Setting();

public:
	GameDepthstencil();
	~GameDepthstencil();
};

