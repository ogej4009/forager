#include "GameIdxBuffer.h"



GameIdxBuffer::GameIdxBuffer()
{
}


GameIdxBuffer::~GameIdxBuffer()
{
}


// DXGI_FORMAT _Fmt // unsigned int인지 아니면 2바이트 인트인지 포맷
// UINT _iDXCount,  // 인덱스 개수
// UINT _iDXSize,  // unsigned int인지 아니면 2바이트 인트인지
// D3D11_USAGE _VTXUSAGE, 
// void* _Data
bool GameIdxBuffer::Create(DXGI_FORMAT _Fmt, UINT _iDXCount, UINT _iDXSize, D3D11_USAGE _VTXUSAGE, void* _Data)
{
	m_IDXFmt = _Fmt;
	m_IDXSize = _iDXSize;
	m_IDXCount = _iDXCount;

	m_BufferDesc.ByteWidth = m_IDXCount * m_IDXSize;
	m_BufferDesc.Usage = _VTXUSAGE;

	if (D3D11_USAGE::D3D11_USAGE_DYNAMIC == m_BufferDesc.Usage)
	{
		m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	m_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA DS = D3D11_SUBRESOURCE_DATA();
	GameTFunc::ZERO(DS);
	DS.pSysMem = _Data;

	HRESULT RS = GameDevice::MainDevice()->CreateBuffer(&m_BufferDesc, &DS, &m_pBuffer);
	if (S_OK != RS)
	{
		CodeEmbeddedErrorDetection;
		return false;
	}

	return true;


}