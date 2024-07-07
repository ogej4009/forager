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
	// DirectX:: 는 그래픽카드의 메모리와 데이터관리를 위해 제공되는 것이다. 

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

	void RenderBegin(); // 그리기 시작하기 전에 깨끗히 지워서 그릴 준비.
	// 이 두 함수 사이에서 랜더링
	void RenderEnd(); // 여태까지 자신에게 그려진걸 출력하라는 함수

private:
	bool CreateSC(); // 스왑체인
	bool CreateDS(); // 깊이 버퍼
	bool CreateVP(); // 뷰포트

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

