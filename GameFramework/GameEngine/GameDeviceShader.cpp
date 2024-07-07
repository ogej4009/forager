#include "GameDevice.h"
#include <vector>
#include <GameDirectory.h>
#include "GameVertex.h"
#include "GameVtxShader.h"
#include "GamePixShader.h"
#include "GameConstBuffer.h"

void GameDevice::ShaderInit()
{
	GameDirectory m_Dir;
	m_Dir.MoveParent(L"GameFramework");
	m_Dir.Move(L"GameShader");

	{
		S_Ptr<GameVtxShader> Vtx_Ptr = GameVtxShader::Load(m_Dir.CreateGameFilePath(L"SPRITE2D.hlsl"), L"VS_SPRITE2D", 5, 0);
		Vtx_Ptr->LayOut.AddLayOut("POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0);
		Vtx_Ptr->LayOut.AddLayOut("TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0);
		Vtx_Ptr->LayOut.EndLayOut("COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0);
		Vtx_Ptr->CB<CTransformData>(L"CB_TRANSDATA", 0);
		Vtx_Ptr->CB<CVector>(L"CB_CUT", 1);

		S_Ptr<GamePixShader> Pix_Ptr = GamePixShader::Load(m_Dir.CreateGameFilePath(L"SPRITE2D.hlsl"), L"PS_SPRITE2D", 5, 0);
		Pix_Ptr->CB<CVector>(L"CB_COLOR", 0);
		Pix_Ptr->TEX(L"TEX2D", 0);
		Pix_Ptr->SMP(L"LSMP", 0);
		Pix_Ptr->SMP(L"PSMP", 1);
	}

	{
		S_Ptr<GameVtxShader> Vtx_Ptr = GameVtxShader::Load(m_Dir.CreateGameFilePath(L"DEBUG2D.hlsl"), L"VS_DEBUG2D", 5, 0);
		Vtx_Ptr->LayOut.EndLayOut("POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0);
		Vtx_Ptr->CB<CTransformData>(L"CB_TRANSDATA", 0);

		S_Ptr<GamePixShader> Pix_Ptr = GamePixShader::Load(m_Dir.CreateGameFilePath(L"DEBUG2D.hlsl"), L"PS_DEBUG2D", 5, 0);
		Pix_Ptr->CB<CVector>(L"CB_DEBUG_COLOR", 0);
	}

}