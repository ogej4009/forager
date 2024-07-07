#include "GameTexture.h"


GameTexture::GameTexture()
	: m_pDSV(nullptr)
	, m_pRTV(nullptr)
	, m_pSRV(nullptr)
	, m_pTex(nullptr)
{
}

GameTexture::~GameTexture()
{
	if (nullptr != m_pRTV)
	{
		m_pRTV->Release();
		m_pRTV = nullptr;
	}

	if (nullptr != m_pDSV)
	{
		m_pDSV->Release();
		m_pDSV = nullptr;
	}

	if (nullptr != m_pSRV)
	{
		m_pSRV->Release();
		m_pSRV = nullptr;
	}

	if (nullptr != m_pTex)
	{
		m_pTex->Release();
		m_pTex = nullptr;
	}

}

bool GameTexture::Load()
{
	if (m_Path.PathData().IsExt(L"DDS") || m_Path.PathData().IsExt(L"dds"))
	{

	}
	else if (m_Path.PathData().IsExt(L"TGA") || m_Path.PathData().IsExt(L"tga"))
	{

	}
	else
	{
		if (S_OK != DirectX::LoadFromWICFile(m_Path, DirectX::WIC_FLAGS_NONE, nullptr, m_Image))
		{
			CodeEmbeddedErrorDetection;
			return false;
		}
	}

	if (S_OK != DirectX::CreateShaderResourceView(
		GameDevice::MainDevice(),
		m_Image.GetImages(),
		m_Image.GetImageCount(),
		m_Image.GetMetadata(),
		&m_pSRV))
	{
		CodeEmbeddedErrorDetection;
		return false;
	}

	m_W = m_Image.GetMetadata().width;
	m_H = m_Image.GetMetadata().height;

	return true;
}

void GameTexture::Setting(GameShader::SHADER_TYPE _Type, int _Index)
{
	switch (_Type)
	{
	case GameShader::ST_VS:
		VSSetting(_Index);
		break;
	case GameShader::ST_HS:
		HSSetting(_Index);
		break;
	case GameShader::ST_DS:
		DSSetting(_Index);
		break;
	case GameShader::ST_GS:
		GSSetting(_Index);
		break;
	case GameShader::ST_PS:
		PSSetting(_Index);
		break;
	default:
		break;
	}
}

void GameTexture::VSSetting(int _Index)
{
	GameDevice::MainContext()->VSSetShaderResources(_Index, 1, &m_pSRV);
}

void GameTexture::HSSetting(int _Index)
{
	GameDevice::MainContext()->HSSetShaderResources(_Index, 1, &m_pSRV);
}

void GameTexture::DSSetting(int _Index)
{
	GameDevice::MainContext()->DSSetShaderResources(_Index, 1, &m_pSRV);
}

void GameTexture::GSSetting(int _Index)
{
	GameDevice::MainContext()->GSSetShaderResources(_Index, 1, &m_pSRV);
}

void GameTexture::PSSetting(int _Index)
{
	GameDevice::MainContext()->PSSetShaderResources(_Index, 1, &m_pSRV);
}
