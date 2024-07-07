#include "GameDevice.h"
#include "GameMaterial.h"

void GameDevice::MaterialInit()
{

	{
		S_Ptr<GameMaterial> RD = GameMaterial::Create(L"SPRITE2D");
		RD->VTXShader(L"SPRITE2D.hlsl");
		RD->PIXShader(L"SPRITE2D.hlsl");
		RD->BLEND(L"DEF_BLEND");
		RD->RASTERIZER(L"NONE2D");
		RD->DEPTHSTENCIL(L"DEF_DEPTH");
	}

	{
		S_Ptr<GameMaterial> RD = GameMaterial::Create(L"DEBUG2D");
		RD->VTXShader(L"DEBUG2D.hlsl");
		RD->PIXShader(L"DEBUG2D.hlsl");
		RD->BLEND(L"DEF_BLEND");
		RD->RASTERIZER(L"NONE2D");
		RD->DEPTHSTENCIL(L"DEF_DEPTH");
	}

}