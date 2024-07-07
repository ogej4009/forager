#pragma once
#include <GameRes.h>
#include "GameShader.h"
#include <vector>


class GameVtxShader : public GameShader, public GameRes<GameVtxShader>
{
public:
	static S_Ptr<GameVtxShader> Load(const GameString& _Path, const GameString& _FuncName, unsigned int _VH, unsigned int _VL)
	{
		GameString Name = _Path.PathData().ArrFullFile;
		GameVtxShader* NewRes = CreateRes(Name);
		NewRes->m_Path = _Path;
		if (false == NewRes->Load(_VH, _VL, _FuncName)) { CodeEmbeddedErrorDetection; }
		return NewRes;
	}

public:
	bool Load(unsigned int _VH, unsigned int _VL, const GameString& _FuncName)
	{
		D3D_SHADER_MACRO _MAC;
		_MAC.Definition = nullptr;
		_MAC.Name = nullptr;
		return Load(_VH, _VL, _FuncName, _MAC, nullptr);
	}

	bool Load(unsigned int _VH, unsigned int _VL, const GameString& _FuncName, D3D_SHADER_MACRO _MAC, ID3DInclude* _Inc);

public:
	class CInputlayout : public GameRef
	{
		friend GameVtxShader;

	private:
		GameVtxShader* m_pParent;
		UINT m_Offset;
		ID3D11InputLayout* m_LayOut;
		std::vector<D3D11_INPUT_ELEMENT_DESC> m_ArrInputData;

	public:
		void AddLayOut(
			const char* _SmtName,
			unsigned int _Index,
			DXGI_FORMAT _Format,
			unsigned int _inputSlot,
			unsigned int _IDSR = 0,
			D3D11_INPUT_CLASSIFICATION _InputClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA
		);

		void EndLayOut(
			const char* _SmtName,
			unsigned int _Index,
			DXGI_FORMAT _Format,
			unsigned int _inputSlot,
			unsigned int _IDSR = 0,
			D3D11_INPUT_CLASSIFICATION _InputClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA
		);

	public:
		CInputlayout(GameVtxShader* _pParent) : m_pParent(_pParent), m_Offset(0), m_LayOut(nullptr) {}
		~CInputlayout() { if (nullptr != m_LayOut) { m_LayOut->Release(); } }
	};

	friend CInputlayout;

public:
	void Setting() override;

private:
	ID3D11VertexShader* m_pVTXPTR;

public:
	CInputlayout LayOut;

public:
	GameVtxShader();
	virtual ~GameVtxShader();
};

