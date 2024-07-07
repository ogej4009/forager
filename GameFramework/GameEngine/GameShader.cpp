#include "GameShader.h"
#include "GameIdxBuffer.h"
#include "GameConstBuffer.h"


GameShader::GameShader(SHADER_TYPE _Type)
	: m_Type(_Type)
{
}

GameShader::~GameShader()
{
	if (nullptr != m_ErrBlob)
	{
		m_ErrBlob->Release();
	}

	if (nullptr != m_Blob)
	{
		m_Blob->Release();
	}
}

void GameShader::CShaderDataParsing(GameString& _Path)
{
}

void GameShader::CB(const GameString& _Name, unsigned int _uiReg, unsigned int _Size, const type_info* _Type)
{
	GameConstBuffer* NewCB = new GameConstBuffer();
	NewCB->Create(m_Type, _uiReg, _Size);
	NewCB->TypeSetting(_Type);
	m_CB.insert(std::map<GameString, S_Ptr<GameConstBuffer>>::value_type(_Name, NewCB));
}

void GameShader::TEX(const GameString& _Name, unsigned int _uiReg)
{
	m_TEX.insert(std::map<GameString, unsigned int>::value_type(_Name, _uiReg));
}

void GameShader::SMP(const GameString& _Name, unsigned int _uiReg)
{
	m_SMP.insert(std::map<GameString, unsigned int>::value_type(_Name, _uiReg));
}