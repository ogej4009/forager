#include "GameConstBuffer.h"

#include "GameDevice.h"


GameConstBuffer::GameConstBuffer()
{
}

GameConstBuffer::~GameConstBuffer()
{
}

bool GameConstBuffer::Create(GameShader::SHADER_TYPE _SHADER, unsigned int _uiReg, unsigned int _Size) {

	SettingInit(_SHADER, _uiReg);

	m_BufferDesc.ByteWidth = _Size;
	m_BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HRESULT RS = GameDevice::MainDevice()->CreateBuffer(&m_BufferDesc, nullptr, &m_pBuffer);
	if (S_OK != RS)
	{
		CodeEmbeddedErrorDetection;
		return false;
	}

	return true;
}

void GameConstBuffer::SettingInit(GameShader::SHADER_TYPE _SHADER, unsigned int _uiReg)
{
	switch (_SHADER)
	{
	case GameShader::ST_VS:
		m_UpdateFunc = &GameConstBuffer::VSSetting;
		break;
	case GameShader::ST_HS:
		m_UpdateFunc = &GameConstBuffer::HSSetting;
		break;
	case GameShader::ST_DS:
		m_UpdateFunc = &GameConstBuffer::DSSetting;
		break;
	case GameShader::ST_GS:
		m_UpdateFunc = &GameConstBuffer::GSSetting;
		break;
	case GameShader::ST_PS:
		m_UpdateFunc = &GameConstBuffer::PSSetting;
		break;
	default:
		break;
	}

	m_uiReg = _uiReg;
}

void GameConstBuffer::Setting()
{
	(this->*m_UpdateFunc)();
}

void GameConstBuffer::VSSetting()
{
	GameDevice::MainContext()->VSSetConstantBuffers(m_uiReg, 1, &m_pBuffer);
}

void GameConstBuffer::HSSetting()
{
	GameDevice::MainContext()->HSSetConstantBuffers(m_uiReg, 1, &m_pBuffer);
}

void GameConstBuffer::DSSetting()
{
	GameDevice::MainContext()->DSSetConstantBuffers(m_uiReg, 1, &m_pBuffer);
}

void GameConstBuffer::GSSetting()
{
	GameDevice::MainContext()->GSSetConstantBuffers(m_uiReg, 1, &m_pBuffer);
}

void GameConstBuffer::PSSetting()
{
	GameDevice::MainContext()->PSSetConstantBuffers(m_uiReg, 1, &m_pBuffer);
}

void GameConstBuffer::SettingData(void* _Ptr, unsigned int _Size)
{
	// m_SubMap.pData = Ptr;

	// 컴퓨트 쉐이더를 사용할때 네번째 0값이 바뀔것이다.
	GameDevice::MainContext()->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_SubMap);

	memcpy_s(m_SubMap.pData, m_BufferDesc.ByteWidth, _Ptr, _Size);

	GameDevice::MainContext()->Unmap(m_pBuffer, 0);

}