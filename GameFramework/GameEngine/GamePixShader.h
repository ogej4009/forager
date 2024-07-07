#pragma once
#include <GameRes.h>
#include "GameShader.h"


class GamePixShader : public GameShader, public GameRes<GamePixShader>
{
public:
	static S_Ptr<GamePixShader> Load(const GameString& _Path, const GameString& _FuncName, unsigned int _VH, unsigned int _VL)
	{
		GameString Name = _Path.PathData().ArrFullFile;
		GamePixShader* NewRes = CreateRes(Name);
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

private:
	ID3D11PixelShader* m_pPIXPTR;

public:
	void Setting() override;

public:
	GamePixShader();
	virtual ~GamePixShader();
};

