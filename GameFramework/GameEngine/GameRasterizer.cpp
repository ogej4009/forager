#include "GameRasterizer.h"


GameRasterizer::GameRasterizer()
	: m_pRasterizer(nullptr)
{
}

GameRasterizer::~GameRasterizer()
{
	if (nullptr != m_pRasterizer)
	{
		m_pRasterizer->Release();
	}
}


bool GameRasterizer::Create(const D3D11_RASTERIZER_DESC& _Decs)
{
	m_Desc = _Decs;

	if (S_OK != GameDevice::MainDevice()->CreateRasterizerState(&m_Desc, &m_pRasterizer))
	{
		CodeEmbeddedErrorDetection;
		return false;
	}

	return true;
}

void GameRasterizer::Setting()
{
	GameDevice::MainContext()->RSSetState(m_pRasterizer);
}