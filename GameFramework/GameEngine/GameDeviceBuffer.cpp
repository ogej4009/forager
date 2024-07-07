#include "GameDeviceBuffer.h"
#include <GameTFunc.h>


GameDeviceBuffer::GameDeviceBuffer() : m_pBuffer(nullptr)
{
	GameTFunc::ZERO(m_BufferDesc);
}

GameDeviceBuffer::~GameDeviceBuffer()
{
	if (nullptr != m_pBuffer)
	{
		m_pBuffer->Release();
		m_pBuffer = nullptr;
	}
}
