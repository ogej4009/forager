#include "GamePixShader.h"


GamePixShader::GamePixShader() : GameShader(SHADER_TYPE::ST_PS), m_pPIXPTR(nullptr)
{
}

GamePixShader::~GamePixShader()
{
	if (nullptr != m_pPIXPTR)
	{
		m_pPIXPTR->Release();
	}
}

// 5.0 
bool GamePixShader::Load(unsigned int _VH, unsigned int _VL, const GameString& _FuncName, D3D_SHADER_MACRO _MAC, ID3DInclude* _Inc)
{
	VerSetting(_VH, _VL);
	// 버전을 문자열로 알려줘야 한다.

	unsigned int _Flag = 0;

#ifdef _DEBUG
	_Flag = D3D10_SHADER_DEBUG;
#endif


	char Arr[256] = { 0 };

	sprintf_s(Arr, "ps_%d_%d", _VH, _VL);



	std::string Name = _FuncName;


	HRESULT RS = D3DCompileFromFile(m_Path, &_MAC, _Inc, Name.c_str(), Arr, _Flag, 0, &m_Blob, &m_ErrBlob);

	if (S_OK != RS)
	{
		std::string Error = (char*)m_ErrBlob->GetBufferPointer();

		CodeEmbeddedErrorDetection;
		return false;
	}

	RS = GameDevice::MainDevice()->CreatePixelShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_pPIXPTR);

	if (nullptr == m_pPIXPTR)
	{
		CodeEmbeddedErrorDetection;
		return false;
	}

	return true;
}


void GamePixShader::Setting()
{
	if (nullptr != m_pPIXPTR)
	{
		GameDevice::MainContext()->PSSetShader(m_pPIXPTR, nullptr, 0);
	}
}