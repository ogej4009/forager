#pragma once
#include "GameDevice.h"
#include "GameShader.h"
#include <GameRes.h>
#include <DirectXTex.h>

#pragma comment(lib, "DirectXTex.lib")
// ���� : ��Ʈ�� ����
// float�� ���� �� �ִ� 2���� �迭


class GameTexture : public GameRes<GameTexture>
{
private:
	DirectX::ScratchImage m_Image;
	size_t m_W;
	size_t m_H;

	ID3D11Resource* m_pTex;

	ID3D11RenderTargetView* m_pRTV;
	ID3D11DepthStencilView* m_pDSV;
	ID3D11ShaderResourceView* m_pSRV;


public:
	ID3D11RenderTargetView* RTV() { return m_pRTV; }
	ID3D11DepthStencilView* DSV() { return m_pDSV; }
	ID3D11ShaderResourceView* SRV() { return m_pSRV; }

public:
	static S_Ptr<GameTexture> Load(const GameString& _Path)
	{
		GameString Name = _Path.PathData().ArrFullFile;
		GameTexture* NewRes = CreateRes(Name);
		NewRes->m_Path = _Path;
		if (false == NewRes->Load()) { CodeEmbeddedErrorDetection; }
		return NewRes;
	}

	bool Load();
	void Setting(GameShader::SHADER_TYPE _Type, int _Index);

	void VSSetting(int _Index);
	void HSSetting(int _Index);
	void DSSetting(int _Index);
	void GSSetting(int _Index);
	void PSSetting(int _Index);

public:
	GameTexture();
	~GameTexture();
};
