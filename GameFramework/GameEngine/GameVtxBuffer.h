#pragma once
#include "GameDeviceBuffer.h"
#include <vector>

// ���ø� �����
// �������� �ƴѵ� ���߻���� �ϰԵǸ�
// ���� A���� virtual�� �ְ�
// B���� virtual�� ������ 
// �����Լ� ���̺��� 2�� ����� �ȴ�.

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

