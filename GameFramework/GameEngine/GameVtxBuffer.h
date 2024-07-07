#pragma once
#include "GameDeviceBuffer.h"
#include <vector>

// 템플릿 상속은
// 문제점은 아닌데 다중상속을 하게되면
// 만약 A에도 virtual이 있고
// B에도 virtual이 있으면 
// 가상함수 테이블이 2개 생기게 된다.

class GameVtxBuffer : public GameRes<GameVtxBuffer>, public GameDeviceBuffer
{
public:
	template<typename T>
	static S_Ptr<GameVtxBuffer> Create(const GameString& _Name, std::vector<T>& _Vec, D3D11_USAGE _VTXUSAGE)
	{
		if (0 >= _Vec.size())
		{
			CodeEmbeddedErrorDetection;
			return nullptr;
		}

		GameVtxBuffer* NewRes = CreateRes(_Name);
		NewRes->Create((UINT)_Vec.size(), sizeof(_Vec[0]), _VTXUSAGE, &_Vec[0]);
		return NewRes;
	}

	static S_Ptr<GameVtxBuffer> Create(const GameString& _Name, UINT _VTXCOUNT, UINT _VTXSIZE, D3D11_USAGE _VTXUSAGE, void* _DATA)
	{
		GameVtxBuffer* NewRes = CreateRes(_Name);
		NewRes->Create(_VTXCOUNT, _VTXSIZE, _VTXUSAGE, _DATA);
		return NewRes;
	}

public:
	bool Create(UINT _VTXCOUNT, UINT _VTXSIZE, D3D11_USAGE _VTXUSAGE, void* _Data);

private:
	UINT m_VTXSize;
	UINT m_VTXCount;

public:
	UINT VTXSize()
	{
		return m_VTXSize;
	}

	UINT VTXCount()
	{
		return m_VTXCount;
	}

public:
	GameVtxBuffer();
	GameVtxBuffer(const GameString& _Name, UINT _VTXCOUNT, UINT _VTXSIZE, D3D11_USAGE _VTXUSAGE, void* _DATA);
	~GameVtxBuffer();
};

