#include "GameMaterial.h"
#include "GameVtxShader.h"
#include "GamePixShader.h"
#include "GameBlend.h"
#include "GameRasterizer.h"
#include "GameDepthStencil.h"


GameShader* GameMaterial::LastShader[5];
GameBlend* GameMaterial::LastBLEND = nullptr;
GameRasterizer* GameMaterial::LastRASTERIZER = nullptr;
GameDepthstencil* GameMaterial::LastDEPTHSTENCIL = nullptr;


GameMaterial::GameMaterial()
	: m_IsClone(false)
{
	m_SHADER.resize(GameShader::ST_MAX);
}

GameMaterial::GameMaterial(const GameMaterial& _Other)
	: m_VTXShader(_Other.m_VTXShader)
	, m_PIXShader(_Other.m_PIXShader)
	, m_BLEND(_Other.m_BLEND)
	, m_RASTERIZER(_Other.m_RASTERIZER)
	, m_DEPTHSTENCIL(_Other.m_DEPTHSTENCIL)
	, m_IsClone(true)
{
}


GameMaterial::~GameMaterial()
{
}


void GameMaterial::VTXShader(const GameString& _Name)
{
	m_VTXShader = GameVtxShader::Find(_Name);

	if (nullptr == m_VTXShader)
	{
		CodeEmbeddedErrorDetection;
	}

	m_SHADER[m_VTXShader->ShType()] = m_VTXShader;
}

void GameMaterial::PIXShader(const GameString& _Name)
{
	m_PIXShader = GamePixShader::Find(_Name);

	if (nullptr == m_PIXShader)
	{
		CodeEmbeddedErrorDetection;
	}

	m_SHADER[m_PIXShader->ShType()] = m_PIXShader;
}

void GameMaterial::BLEND(const GameString& _Name)
{
	m_BLEND = GameBlend::Find(_Name);

	if (nullptr == m_BLEND)
	{
		CodeEmbeddedErrorDetection;
	}
}

void GameMaterial::RASTERIZER(const GameString& _Name)
{
	m_RASTERIZER = GameRasterizer::Find(_Name);

	if (nullptr == m_RASTERIZER)
	{
		CodeEmbeddedErrorDetection;
	}
}

void GameMaterial::DEPTHSTENCIL(const GameString& _Name)
{
	m_DEPTHSTENCIL = GameDepthstencil::Find(_Name);

	if (nullptr == m_DEPTHSTENCIL)
	{
		CodeEmbeddedErrorDetection;
	}
}


void GameMaterial::Setting()
{
	for (size_t i = 0; i < m_SHADER.size(); ++i)
	{
		if (nullptr == m_SHADER[i] && LastShader[i] == m_SHADER[i])
		{
			continue;
		}

		m_SHADER[i]->Setting();
		LastShader[i] = m_SHADER[i];
	}

	if (nullptr != m_BLEND && LastBLEND != m_BLEND)
	{
		m_BLEND->Setting();
		LastBLEND = m_BLEND;
	}

	if (nullptr != m_RASTERIZER && LastRASTERIZER != m_RASTERIZER)
	{
		m_RASTERIZER->Setting();
		LastRASTERIZER = m_RASTERIZER;
	}

}


bool GameMaterial::Create()
{
	return true;
}


S_Ptr<GameMaterial> GameMaterial::Clone()
{
	return new GameMaterial(*this);
}

