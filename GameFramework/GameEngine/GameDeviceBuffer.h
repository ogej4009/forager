#pragma once
#include <GameRes.h>
#include "GameDevice.h"

// 버퍼 : 그래픽 카드에 보내는 데이터

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

