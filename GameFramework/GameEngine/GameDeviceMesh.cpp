#include "GameDevice.h"
#include "GameVtxBuffer.h"
#include "GameIdxBuffer.h"
#include "GameVertex.h"
#include "GameMesh.h"
#include <vector>

void GameDevice::MeshInit()
{
#pragma region SPRITERECT
	{
		std::vector<GameVertex> ArrVTX;
		ArrVTX.resize(4);

		ArrVTX[0].m_Pos = { -0.5f, 0.5f, 0.0f, 1.0f };
		ArrVTX[1].m_Pos = { 0.5f, 0.5f, 0.0f, 1.0f };
		ArrVTX[2].m_Pos = { 0.5f, -0.5f, 0.0f, 1.0f };
		ArrVTX[3].m_Pos = { -0.5f, -0.5f, 0.0f, 1.0f };

		ArrVTX[0].m_Uv = { 0.0f, 0.0f, 0.0f, 0.0f };
		ArrVTX[1].m_Uv = { 1.0f, 0.0f, 0.0f, 0.0f };
		ArrVTX[2].m_Uv = { 1.0f, 1.0f, 0.0f, 0.0f };
		ArrVTX[3].m_Uv = { 0.0f, 1.0f, 0.0f, 0.0f };

		ArrVTX[0].m_Color = CVector::WHITE;
		ArrVTX[1].m_Color = CVector::WHITE;
		ArrVTX[2].m_Color = CVector::WHITE;
		ArrVTX[3].m_Color = CVector::WHITE;


		GameVtxBuffer::Create(L"RECT2D", ArrVTX, D3D11_USAGE::D3D11_USAGE_DEFAULT);
		std::vector<UINT> ArrIDX = { 0, 1, 2, 0, 2, 3 };

		GameIdxBuffer::Create(L"RECT2D", ArrIDX, D3D11_USAGE::D3D11_USAGE_DEFAULT);
		GameMesh::Create(L"RECT2D", L"RECT2D", L"RECT2D");

	}
#pragma endregion

#pragma region FULLRECT
	{
		std::vector<GameVertex> ArrVTX;
		ArrVTX.resize(4);

		ArrVTX[0].m_Pos = { -1.0f, 1.0f, 0.0f, 1.0f };
		ArrVTX[1].m_Pos = { 1.0f, 1.0f, 0.0f, 1.0f };
		ArrVTX[2].m_Pos = { 1.0f, -1.0f, 0.0f, 1.0f };
		ArrVTX[3].m_Pos = { -1.0f, -1.0f, 0.0f, 1.0f };

		ArrVTX[0].m_Uv = { 0.0f, 0.0f, 0.0f, 0.0f };
		ArrVTX[1].m_Uv = { 1.0f, 0.0f, 0.0f, 0.0f };
		ArrVTX[2].m_Uv = { 1.0f, 1.0f, 0.0f, 0.0f };
		ArrVTX[3].m_Uv = { 0.0f, 1.0f, 0.0f, 0.0f };

		ArrVTX[0].m_Color = { 1.0f, 0.0f, 0.0f, 1.0f };
		ArrVTX[1].m_Color = { 0.0f, 0.0f, 1.0f, 1.0f };
		ArrVTX[2].m_Color = { 0.0f, 1.0f, 0.0f, 1.0f };
		ArrVTX[3].m_Color = { 0.0f, 1.0f, 1.0f, 1.0f };

		GameVtxBuffer::Create(L"FULL_RECT", ArrVTX, D3D11_USAGE::D3D11_USAGE_DEFAULT);
		std::vector<UINT> ArrIDX = { 0, 1, 2, 0, 2, 3 };

		GameIdxBuffer::Create(L"FULL_RECT", ArrIDX, D3D11_USAGE::D3D11_USAGE_DEFAULT);
		GameMesh::Create(L"FULL_RECT", L"FULL_RECT", L"FULL_RECT");
	}
#pragma endregion

#pragma region DEBUGRECT
	{
		std::vector<CVector> ArrVTX;
		ArrVTX.resize(4);

		ArrVTX[0] = { -0.5f, 0.5f, 0.0f, 1.0f };
		ArrVTX[1] = { 0.5f, 0.5f, 0.0f, 1.0f };
		ArrVTX[2] = { 0.5f, -0.5f, 0.0f, 1.0f };
		ArrVTX[3] = { -0.5f, -0.5f, 0.0f, 1.0f };

		GameVtxBuffer::Create(L"DEBUG_RECT2D", ArrVTX, D3D11_USAGE::D3D11_USAGE_DEFAULT);

		std::vector<UINT> ArrIDX = { 0, 1, 2, 3, 0 };
		GameIdxBuffer::Create(L"DEBUG_RECT2D", ArrIDX, D3D11_USAGE::D3D11_USAGE_DEFAULT);
		GameMesh::Create(L"DEBUG_RECT2D", L"DEBUG_RECT2D", L"DEBUG_RECT2D");
	}
#pragma endregion
}