#include "GameVtxBuffer.h"


GameVtxBuffer::GameVtxBuffer()
{
}

GameVtxBuffer::GameVtxBuffer(const GameString& _Name, UINT _VTXCOUNT, UINT _VTXSIZE, D3D11_USAGE _VTXUSAGE, void* _DATA)
{
	AddRes(_Name, this);
	Create(_VTXCOUNT, _VTXSIZE, _VTXUSAGE, _DATA);
}

GameVtxBuffer::~GameVtxBuffer()
{
}

// _Data 는 로컬상태에서의 점 위치를 세팅해서 넣어준다. 초기값을 의미. 
bool GameVtxBuffer::Create(UINT _VTXCOUNT, UINT _VTXSIZE, D3D11_USAGE _VTXUSAGE, void* _Data)
{
	m_VTXSize = _VTXSIZE;
	m_VTXCount = _VTXCOUNT;
	m_BufferDesc.ByteWidth = m_VTXSize * m_VTXCount;
	m_BufferDesc.Usage = _VTXUSAGE;

	if (D3D11_USAGE::D3D11_USAGE_DYNAMIC == m_BufferDesc.Usage)
	{
		m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

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


