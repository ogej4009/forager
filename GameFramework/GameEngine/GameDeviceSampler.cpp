#include "GameDevice.h"
#include "GameSampler.h"

void GameDevice::SmpInit()
{
	{
		D3D11_SAMPLER_DESC SmpData;

		SmpData.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;

		SmpData.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		SmpData.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		SmpData.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		// ����
		// SmpData.BorderColor
		SmpData.ComparisonFunc = D3D11_COMPARISON_NEVER;
		//D3D11_FILTER_ANISOTROPIC; ����϶� �ǹ̰� ������ �Ⱦ���. 
		SmpData.MaxAnisotropy = 0;
		SmpData.MinLOD = -FLT_MAX;
		SmpData.MaxLOD = FLT_MAX;
		SmpData.MipLODBias = 1.0f;

		GameSampler::Create(L"LSMP", SmpData);
	}

	{

		D3D11_SAMPLER_DESC SmpData;

		SmpData.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;

		SmpData.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		SmpData.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		SmpData.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;

		SmpData.ComparisonFunc = D3D11_COMPARISON_NEVER;
		SmpData.MaxAnisotropy = 0;
		SmpData.MinLOD = -FLT_MAX;
		SmpData.MaxLOD = FLT_MAX;
		SmpData.MipLODBias = 1.0f;

		GameSampler::Create(L"PSMP", SmpData);
	}
}