#include "GameDevice.h"
#include "GameFrameDebug.h"

GameDevice* GameDevice::g_pMainDevice = nullptr;
ID3D11Device* GameDevice::m_MainDevice = nullptr;
ID3D11DeviceContext* GameDevice::m_MainContext = nullptr;

std::map<GameWin*, S_Ptr<GameDevice>> GameDevice::m_DeviceMap;

void GameDevice::CreateDevice(S_Ptr<GameWin> _Win)
{
	// ��������� ���� ���� �� �ִ�. 
	GameDevice* NewDevice = new GameDevice(_Win);
	m_DeviceMap.insert(std::map<GameWin*, S_Ptr<GameDevice>>::value_type(_Win, NewDevice));
}

void GameDevice::DefInit()
{
	MeshInit();
	ShaderInit();
	SmpInit();
	BlendInit();
	RasterizerInit();
	DepthStencilInit();
	MaterialInit();
	FontInit();
	GameFrameDebug::Init();
}

GameDevice::GameDevice(GameWin* _ParentWin)
	: m_ParentWin(_ParentWin)
	, m_pDevice(nullptr)
	, m_pContext(nullptr)
	, m_pBackBufferTex(nullptr)
	, m_pDepthStencilTex(nullptr)
	, m_DefInit(false)
{
	if (nullptr == m_ParentWin)
	{
		CodeEmbeddedErrorDetection;
	}

	int iFlag = 0;

#ifdef _DEBUG
	// ����� ���� ������.
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif 
	// ����̽� ���� ����̽��� ������ �˷��ִ°�.
	// �Ⱦ��ڽ��ϴ�.D3D_FEATURE_LEVEL_11_1
	// ���̴� ���� 5�� ����ϱ� ���Ѱ�
	// ���� ���̴� ������ D3D_FEATURE_LEVEL_9
	// ������ ������ �Ⱦ��Ŵ�.
	D3D_FEATURE_LEVEL eLv = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	// �ʱ�ȭ �÷�.
	m_ClearColor = CVector(0.0F, 0.0F, 1.0F, 1.0F);

	HRESULT Result;

	//_In_opt_ IDXGIAdapter* pAdapter, // ����̽� ���鶧 ���� Ư���� § com�� �������̽� 
	//D3D_DRIVER_TYPE DriverType, // ���� .
	//HMODULE Software,
	//UINT Flags,
	//_In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
	//UINT FeatureLevels,
	//UINT SDKVersion,
	//_COM_Outptr_opt_ ID3D11Device** ppDevice,
	//_Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
	//_COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext

	Result = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, // ����Ʈ ����� CPU�ε� ������ �ִ�. 
		nullptr, // �׳� ���� ����
		iFlag, // ����� ���� ������. ������� 0 �׳� ������
		nullptr, // ���� ���� �� �ִ����
		0, // D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0 �־��൵ �ɲ���.,
		D3D11_SDK_VERSION, // ���� �����쿡 ��ġ�� SDK���� 
		&m_pDevice,
		&eLv,
		&m_pContext);

	// ȭ���� ������ �Ҽ� �ִ� �غ� �ʿ���
	// m_pDevice // ���ҽ�
	// m_pContext // ������
	// �� ���°�

	if (S_OK != Result || nullptr == m_pDevice || nullptr == m_pContext)
	{
		CodeEmbeddedErrorDetection;
	}

	m_MC = 4;
	Result = m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, m_MC, &m_MQ);
	if (S_OK != Result)
	{
		m_MC = 1;
		m_MQ = 0;
		Result = m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, m_MC, &m_MQ);
		if (S_OK != Result)
		{
			CodeEmbeddedErrorDetection;
		}
	}

	m_MC = 1;
	m_MQ = 0;

	if (false == CreateSC())
	{
		CodeEmbeddedErrorDetection;
	}

	if (false == CreateDS())
	{
		CodeEmbeddedErrorDetection;
	}

	if (false == CreateVP())
	{
		CodeEmbeddedErrorDetection;
	}

	if (false == m_DefInit)
	{
		g_pMainDevice = this;
		m_MainDevice = m_pDevice;
		m_MainContext = m_pContext;

		DefInit();
		m_DefInit = true;
	}

}


GameDevice::~GameDevice()
{
	if (nullptr != m_pDSV)
	{
		m_pDSV->Release();
	}
	if (nullptr != m_pRTV)
	{
		m_pRTV->Release();
	}
	if (nullptr != m_pDepthStencilTex)
	{
		m_pDepthStencilTex->Release();
	}
	if (nullptr != m_pBackBufferTex)
	{
		m_pBackBufferTex->Release();
	}
	if (nullptr != m_pSwapChain)
	{
		m_pSwapChain->Release();
	}
	if (nullptr != m_pContext)
	{
		m_pContext->Release();
	}
	if (nullptr != m_pDevice)
	{
		m_pDevice->Release();
	}
}

bool GameDevice::CreateDS()
{
	// 0~ 1�� ����ϴ� ���� ����� ũ�⸸�� ���۴� ���� �������?
	// �̹����� ������ �׳� 2���� �迭�� �����س��ٰ� �����ϴ°� ���ϴ�. 


	// ID3D11Texture2D* pBackBufferTex = nullptr;

	if (S_OK != m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_pBackBufferTex))
	{
		CodeEmbeddedErrorDetection;
		return false;
	}

	// �����е��� �ؽ�ó�� ���� 
	// �׷���ī�� ���꿡�� ���ϼ� �ִ� �༮�� �ƴϿ���.
	// �׷���ī������ � �ؽ�ó�� �׷��� ������ ���ؼ� ���ϰž�.
	// ������̱� ������ �������� ����Ϸ��� ������� �ƴϴ�.
	// ���ﶧ�� �� ������� �ʿ��ϴ�.
	if (S_OK != m_pDevice->CreateRenderTargetView(m_pBackBufferTex, 0, &m_pRTV))
	{
		CodeEmbeddedErrorDetection;
		return false;
	}

	// ����� �����е��� �ڵ����� ������ �ؽ�ó�� �ε��ϸ�
	// �� ������ �˾Ƽ� ���õȴ�.
	D3D11_TEXTURE2D_DESC TD;
	GameTFunc::ZERO(TD);
	// �ʺ�� ũ�Ⱑ ���� �ؽ�ó �������� �����ִ� ��ó�� ��밡��.
	// �̰� ��Ƽ�ؽ�ó�� ����� �ִ�.
	TD.ArraySize = 1;
	TD.Width = m_ParentWin->Size().uix();
	TD.Height = m_ParentWin->Size().uiy();

	// 3����Ʈ float�� 1����Ʈ ����ε� int�� ����
	// �̶� �뵵�� float��
	// ���� ����
	// int�� ���ٽ� ���۸� �����ϴµ�
	// �� ���ٽǹ��۴�
	// 0~255������ ������ �ȼ��� �����
	// �� ���� �̿��Ҽ� �ִ�.
	// a��� ��ü�� � �׸��׸�����
	// ���ٽǹ��ۿ� 5�� �������
	// ������ �׸��� �ֵ��� ���ٽ� ���۰� 5�� �ִ�
	// ��� ��� ó������ ��� ���� �Ҽ��� �ִ�.
	TD.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	// ���̸� üũ�ϴ� �༮�̶� ������ ī��Ʈ�� �ʿ䰡 ������.
	TD.SampleDesc.Count = 1;
	TD.SampleDesc.Quality = 0;
	TD.MipLevels = 1;

	// D3D11_USAGE_DYNAMIC
	// ������ �ʴ� �׷���ī�� �ȿ��� �־����
	TD.Usage = D3D11_USAGE_DEFAULT;
	// �ؽ�ó �뵵
	// ���� ���۷� ���ڴ�.
	TD.BindFlags = D3D11_BIND_DEPTH_STENCIL;


	m_pDevice->CreateTexture2D(&TD, 0, &m_pDepthStencilTex);
	if (nullptr == m_pDepthStencilTex)
	{
		CodeEmbeddedErrorDetection;
		return false;
	}

	m_pDevice->CreateDepthStencilView(m_pDepthStencilTex, 0, &m_pDSV);
	if (nullptr == m_pDSV)
	{
		CodeEmbeddedErrorDetection;
		return false;
	}

	return true;
	// �̰� ���� �׸��� ������ ����� �ƴϴ�.

}

void GameDevice::DEFRENDERTARGETSET()
{
	// ���̹��۴� m_pDSV;
	// ���� Ÿ���� m_pRTV ����� ����Ÿ��
	m_pContext->OMSetRenderTargets(1, &m_pRTV, m_pDSV);
}

void GameDevice::DEFVIEWPORTSET()
{
	m_pContext->RSSetViewports(1, &m_VP);
}

bool GameDevice::CreateVP()
{
	m_VP.TopLeftX = 0;
	m_VP.TopLeftY = 0;
	m_VP.MinDepth = 0.0f;
	m_VP.MaxDepth = 1.0f;
	m_VP.Width = m_ParentWin->Size().x;
	m_VP.Height = m_ParentWin->Size().y;

	return true;
}

bool GameDevice::CreateSC()
{
	DXGI_SWAP_CHAIN_DESC SCINFO;
	memset(&SCINFO, 0, sizeof(DXGI_SWAP_CHAIN_DESC));

	SCINFO.BufferDesc.Width = m_ParentWin->Size().uix();
	SCINFO.BufferDesc.Height = m_ParentWin->Size().uiy();

	// 60 ������ 
	SCINFO.BufferDesc.RefreshRate.Numerator = 60;
	SCINFO.BufferDesc.RefreshRate.Denominator = 1;

	// HD����Ͷ��
	// DXGI_FORMAT_R32G32B32A32_UINT

	SCINFO.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SCINFO.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SCINFO.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// ȭ�鿡 ����ϴ� �뵵��.
	SCINFO.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// �ִ� ���� ���۶� 
	// ��Ƽ���ø� ����Ƽ�� �Ű澵 �ʿ䰡 ����.
	// ī��Ʈ�� 1�̴�.
	SCINFO.SampleDesc.Quality = 0;
	SCINFO.SampleDesc.Count = 1;
	SCINFO.OutputWindow = m_ParentWin->WINHWND();

	SCINFO.BufferCount = 2;
	// SCINFO.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	// �ֽŹ��� ����
	SCINFO.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SCINFO.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// IDXGISwapChain::ResizeTarget �� ȣ���Ͽ� ���ø����̼��� ��带 
	// ��ȯ �� ���ְ��Ϸ����� �÷��׸� �����Ͻʽÿ�.â���� ��ü ȭ�� 
	// ���� ��ȯ�ϸ� ���� ���α׷� â�� ũ�⿡ �°� ���÷��� 
	// ���(�Ǵ� ����� �ػ�)�� ����˴ϴ�.

	// ��üȭ��
	// ��üȭ�� 
	// ����̽� �ҽ��� �Ͼ���� �ִ�.
	SCINFO.Windowed = true;

	// ���̷�Ʈ 11�� ���̷�Ʈ 9���� ���̵��� ����
	// ���̷�Ʈ 12 ���̷�Ʈ 11���� ���̵��� ����.

	// �ϴ� ���̷�Ʈ 11���� ����ϴ� �޸𸮵��� fmode �� �Ȱ���
	// �޸� ������ release�� �ظ��ϸ� ���� �� ��������� �Ѵ�.
	// ���߿��� ����ü���� ����� ����� �� �����ϴ�.

	// 
	IDXGIDevice* pD = nullptr;
	IDXGIAdapter* pA = nullptr;
	IDXGIFactory* pF = nullptr;

	// "54ec77fa-1377-44e6-8c32-88fd5f44c84c"
	// �����Ѵٰ� �ϴ���// �Ƴ�????
	m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pD);
	if (nullptr == pD)
	{
		CodeEmbeddedErrorDetection;
		return false;
	}

	// ����̽��� ����� ���� �׳༮
	// IDXGIAdapter��ġ�� �����ؼ� ����� �����µ� ����մϴ�. 
	pD->GetParent(__uuidof(IDXGIAdapter), (void**)&pA);
	if (nullptr == pA)
	{
		CodeEmbeddedErrorDetection;
		return false;
	}

	// �� ���̷�Ʈ�� �޸𸮰� �����ɶ� 
	pA->GetParent(__uuidof(IDXGIFactory), (void**)&pF);
	if (nullptr == pF)
	{
		CodeEmbeddedErrorDetection;
		return false;
	}

	// m_pDevice

	if (S_OK != pF->CreateSwapChain(m_pDevice, &SCINFO, &m_pSwapChain))
	{
		CodeEmbeddedErrorDetection;
		return false;
	}

	pF->Release();
	pA->Release();
	pD->Release();

	return true;
}

void GameDevice::RenderBegin()
{
	if (nullptr != m_pContext)
	{
		m_pContext->ClearRenderTargetView(m_pRTV, m_ClearColor.Arr);
		// 0.0f 
		// ���� �ΰ��е�� ������ �ߵ�������.
		// �̰� , 1.0f = 0.0f�� �ʱ�ȭ�س��� �̷��� �����ߴµ� �ϸ�
		// ���� �������� ����.
		m_pContext->ClearDepthStencilView(m_pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

}
void GameDevice::RenderEnd()
{
	if (nullptr != m_pSwapChain)
	{
		m_pSwapChain->Present(0, 0);
	}
}