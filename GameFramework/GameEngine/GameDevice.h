#pragma once
#include <DirectXCollision.h>
#include <DirectXCollision.inl>
#include <DirectXPackedVector.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <GameWin.h>
#include <map>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

class GameDevice : public GameRef
{
private:
	static std::map<GameWin*, S_Ptr<GameDevice>> m_DeviceMap;
	static GameDevice* g_pMainDevice;
	static ID3D11Device* m_MainDevice;
	static ID3D11DeviceContext* m_MainContext;

public:
	static GameDevice* gMainDevice() { return g_pMainDevice; }
	static ID3D11Device* MainDevice() { return m_MainDevice; }
	static ID3D11DeviceContext* MainContext() { return m_MainContext; }

public:
	static void CreateDevice(S_Ptr<GameWin> _Win);

private:
	GameWin* m_ParentWin;
	// DirectX:: �� �׷���ī���� �޸𸮿� �����Ͱ����� ���� �����Ǵ� ���̴�. 

	UINT m_MC;
	UINT m_MQ;
	CVector m_ClearColor;

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pContext;

	IDXGISwapChain* m_pSwapChain;

	ID3D11Texture2D* m_pBackBufferTex;
	ID3D11Texture2D* m_pDepthStencilTex;

	ID3D11RenderTargetView* m_pRTV;
	ID3D11DepthStencilView* m_pDSV;

	D3D11_VIEWPORT m_VP;

public:
	void DEFVIEWPORTSET();
	void DEFRENDERTARGETSET();

	void RenderBegin(); // �׸��� �����ϱ� ���� ������ ������ �׸� �غ�.
	// �� �� �Լ� ���̿��� ������
	void RenderEnd(); // ���±��� �ڽſ��� �׷����� ����϶�� �Լ�

private:
	bool CreateSC(); // ����ü��
	bool CreateDS(); // ���� ����
	bool CreateVP(); // ����Ʈ

	bool m_DefInit;
	void DefInit();
	void MeshInit();
	void FontInit();
	void ShaderInit();
	void SmpInit();
	void BlendInit();
	void RasterizerInit();
	void MaterialInit();
	void DepthStencilInit();

private:
	GameDevice(GameWin* _ParentWin);
	~GameDevice();
};

