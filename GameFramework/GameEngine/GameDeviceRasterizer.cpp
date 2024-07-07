#include "GameDevice.h"
#include "GameRasterizer.h"

void GameDevice::RasterizerInit()
{
	{
		D3D11_RASTERIZER_DESC m_Decs;
		memset(&m_Decs, 0, sizeof(D3D11_RASTERIZER_DESC));

		m_Decs.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		m_Decs.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		m_Decs.MultisampleEnable = FALSE;
		m_Decs.AntialiasedLineEnable = FALSE;

		GameRasterizer::Create(L"NONE2D", m_Decs);
	}

}