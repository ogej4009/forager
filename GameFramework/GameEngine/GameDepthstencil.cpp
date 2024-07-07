#include "GameDepthstencil.h"



GameDepthstencil::GameDepthstencil()
	: m_pDSS(nullptr)
{
}

GameDepthstencil::~GameDepthstencil()
{
	if (nullptr != m_pDSS)
	{
		m_pDSS->Release();
	}
}

bool GameDepthstencil::Create(const D3D11_DEPTH_STENCIL_DESC& _Decs)
{
	m_Decs = _Decs;

	if (S_OK != GameDevice::MainDevice()->CreateDepthStencilState(&m_Decs, &m_pDSS))
	{
		CodeEmbeddedErrorDetection;
		return false;
	}

	return true;
}

void GameDepthstencil::Setting()
{
	GameDevice::MainContext()->OMSetDepthStencilState(m_pDSS, 0);
}