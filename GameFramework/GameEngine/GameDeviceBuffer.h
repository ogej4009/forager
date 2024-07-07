#pragma once
#include <GameRes.h>
#include "GameDevice.h"

// ���� : �׷��� ī�忡 ������ ������

class GameDeviceBuffer
{
protected:
	D3D11_MAPPED_SUBRESOURCE m_SubMap;
	D3D11_BUFFER_DESC m_BufferDesc;
	ID3D11Buffer* m_pBuffer;

public:
	ID3D11Buffer* Buffer()
	{
		return m_pBuffer;
	}

	D3D11_BUFFER_DESC BufferDesc()
	{
		return m_BufferDesc;
	}

public:
	GameDeviceBuffer();
	virtual ~GameDeviceBuffer();
};

