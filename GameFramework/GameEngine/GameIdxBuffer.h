#pragma once
#include "GameDeviceBuffer.h"
#include <vector>

class GameIdxBuffer : public GameRes<GameIdxBuffer>, public GameDeviceBuffer
{
public:
	template<typename T>
	static bool Create(const GameString& _Name, std::vector<T>& _Vec, D3D11_USAGE _USAGE)
	{
		if (0 >= _Vec.size())
		{
			CodeEmbeddedErrorDetection;
			return false;
		}
		return Create(_Name, (UINT)_Vec.size(), sizeof(_Vec[0]), _USAGE, &_Vec[0]);
	}

	static bool Create(const GameString& _Name, UINT _iDXCount, UINT _iDXSize, D3D11_USAGE _USAGE, void* _Data)
	{
		DXGI_FORMAT _Fmt = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;

		if (2 == _iDXSize)
		{
			_Fmt = DXGI_FORMAT::DXGI_FORMAT_R16_UINT;
		}
		else if (4 == _iDXSize) {
			_Fmt = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
		}
		else
		{
			CodeEmbeddedErrorDetection;
		}

		return Create(_Name, _Fmt, _iDXCount, _iDXSize, _USAGE, _Data);
	}

	static bool Create(const GameString& _Name, DXGI_FORMAT _Fmt, UINT _iDXCount, UINT _iDXSize, D3D11_USAGE _USAGE, void* _Data)
	{
		GameIdxBuffer* NewRes = CreateRes(_Name);
		return NewRes->Create(_Fmt, _iDXCount, _iDXSize, _USAGE, _Data);
	}

public:
	bool Create(DXGI_FORMAT _Fmt, UINT _iDXCount, UINT _iDXSize, D3D11_USAGE _USAGE, void* _Data);

private:
	DXGI_FORMAT m_IDXFmt;
	UINT m_IDXSize;
	UINT m_IDXCount;

public:
	DXGI_FORMAT IDXFmt() { return m_IDXFmt; }
	UINT IDXSize() { return m_IDXSize; }
	UINT IDXCount() { return m_IDXCount; }


public:
	GameIdxBuffer();
	~GameIdxBuffer();
};

