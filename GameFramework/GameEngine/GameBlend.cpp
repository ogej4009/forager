#include "GameBlend.h"



GameBlend::GameBlend()
	: m_pBlend(nullptr)
{
}

GameBlend::~GameBlend()
{
	if (nullptr != m_pBlend)
	{
		m_pBlend->Release();
	}
}

bool GameBlend::Create(const D3D11_BLEND_DESC& _Desc)
{
	m_Desc = _Desc;

	if (S_OK != GameDevice::MainDevice()->CreateBlendState(&m_Desc, &m_pBlend))
	{
		CodeEmbeddedErrorDetection;
		return false;
	}

	return true;
}

void GameBlend::Setting()
{
	GameDevice::MainContext()->OMSetBlendState(m_pBlend, nullptr, 0xffffffff);
}
