#include "GameMesh.h"
#include "GameDevice.h"


GameMesh::GameMesh()
{
}

GameMesh::~GameMesh()
{
}

bool GameMesh::Create(const std::vector<GameString>& _VBList, const std::vector<GameString>& _IBList)
{
	for (size_t i = 0; i < _VBList.size(); i++)
	{
		AddVB(_VBList[i]);
	}

	for (size_t i = 0; i < _IBList.size(); i++)
	{
		AddIB(_IBList[i]);
	}
	return true;
}

bool GameMesh::Create(const wchar_t* _VB, const wchar_t* _IB)
{
	AddVB(_VB);
	AddIB(_IB);
	return true;
}

void GameMesh::AddIB(const wchar_t* _Name)
{
	S_Ptr<GameIdxBuffer> Ptr = GameIdxBuffer::Find(_Name);

	if (nullptr == Ptr)
	{
		CodeEmbeddedErrorDetection;
	}

	m_ArrIBBuffer.push_back(Ptr->Buffer());
	m_ArrIBOffset.push_back(0);
	m_ArrIB.push_back(Ptr);
}

void GameMesh::AddVB(const wchar_t* _Name)
{
	S_Ptr<GameVtxBuffer> Ptr = GameVtxBuffer::Find(_Name);

	if (nullptr == Ptr)
	{
		CodeEmbeddedErrorDetection;
	}

	m_ArrVBBuffer.push_back(Ptr->Buffer());
	m_ArrVBSize.push_back(Ptr->VTXSize());
	m_ArrVBOffset.push_back(0);
	m_ArrVB.push_back(Ptr);
}

void GameMesh::SettingVB(UINT _Index)
{
	// IA Input Assembler 인풋 어셈블러
	// OM Output Merger 아웃풋 머저.
	// CGameDevice::MainContext()->OMGetBlendState
	// 5개를 세팅해줬다.
	//   1 2
	// 0 1 2 3 4
		//_In_range_(0, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - 1)  UINT StartSlot, //  시작슬롯 
		//_In_range_(0, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - StartSlot)  UINT NumBuffers, 몇개냐
		//_In_reads_opt_(NumBuffers)  ID3D11Buffer *const *ppVertexBuffers,
		//_In_reads_opt_(NumBuffers)  const UINT *pStrides, // 46바이트 짜리 버텍스. 점하나가 몇바이트냐
		//_In_reads_opt_(NumBuffers)  const UINT *pOffsets	// 버텍스 버퍼의 시작번지
	// 
	GameDevice::MainContext()->IASetVertexBuffers(0, 1, &m_ArrVBBuffer[_Index], &m_ArrVBSize[_Index], &m_ArrVBOffset[_Index]);
}

void GameMesh::SettingIB(UINT _Index)
{
	GameDevice::MainContext()->IASetIndexBuffer(m_ArrIBBuffer[_Index], m_ArrIB[_Index]->IDXFmt(), m_ArrIBOffset[0]);
}


void GameMesh::RenderIndexed(UINT _Index)
{
	GameDevice::MainContext()->DrawIndexed(m_ArrIB[_Index]->IDXCount(), 0, 0);
}