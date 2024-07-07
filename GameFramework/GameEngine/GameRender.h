#pragma once
#include <vector>
#include "GameTransform.h"
#include "GameVtxShader.h"
#include "GamePixShader.h"
#include "GameMesh.h"
#include "GameTexture.h"
#include "GameSampler.h"
#include "GameBlend.h"
#include "GameConstBuffer.h"
#include "GameMaterial.h"
#include "GameVirtualFunc.h"

class GameFrameDebug;
class GameRender;
class GameMesh;
class GameTexture;
class GameSampler;
class GameConstBuffer;
class GameMaterial;

class GameRenderData : public GameVirtualFunc
{
public:
	friend GameRender;

private:
	class CRenderRes
	{
	public:
		unsigned int Slot;
	};

	class CBData : public CRenderRes
	{
	public:
		S_Ptr<GameConstBuffer> CB;
		unsigned int Size;
		bool m_IsLink;
		void* Data;

	public:
		void Reset()
		{
			if (false == m_IsLink && nullptr != Data)
			{
				delete[] Data;
			}
		}

	public:
		CBData()
			: Data(nullptr), m_IsLink(false)
		{
		}
		~CBData()
		{
			Reset();
		}

	};

	class TexData : public CRenderRes
	{
	public:
		S_Ptr<GameTexture> Tex;
	public:
		TexData()
			: Tex(nullptr)
		{
		}

	};


	class SMPData : public CRenderRes
	{
	public:
		S_Ptr<GameSampler> Smp;
	public:
		SMPData()
			: Smp(nullptr)
		{
		}

	};


public:
	friend GameRender;
	friend GameFrameDebug;

private:
	CTransformData* m_pData;
	S_Ptr<GameMesh>				m_Mesh;
	S_Ptr<GameMaterial>			m_Material;
	D3D11_PRIMITIVE_TOPOLOGY	m_DrawMode;

private:
	void MaterialInit();

private:
	std::map<GameShader::SHADER_TYPE, std::map<GameString, TexData>> TexRes;
	std::map<GameShader::SHADER_TYPE, std::map<GameString, CBData>> CBRes;
	std::map<GameShader::SHADER_TYPE, std::map<GameString, SMPData>> SmpRes;

public:
	S_Ptr<GameMaterial>	Material();

public:
	template<typename T>
	void CB(const GameString& _Name, const T& _Value, bool _bLink = false, GameShader::SHADER_TYPE _Type = GameShader::SHADER_TYPE::ST_MAX)
	{
		CBDataCreate(_Name, (void*)&_Value, _bLink, _Type);
	}
	void SMP(const GameString& _Name, const GameString& _SmpName, GameShader::SHADER_TYPE _Type = GameShader::SHADER_TYPE::ST_MAX);
	void TEX(const GameString& _Name, const GameString& _TexName, GameShader::SHADER_TYPE _Type = GameShader::SHADER_TYPE::ST_MAX);
	void TEX(const GameString& _Name, S_Ptr<GameTexture> _Tex, GameShader::SHADER_TYPE _Type = GameShader::SHADER_TYPE::ST_MAX);

private:
	void CBDataCreate(const GameString& _Name, void* _Data, bool _bLink = false, GameShader::SHADER_TYPE _Type = GameShader::SHADER_TYPE::ST_MAX);

public:
	void Render();

public:
	GameRenderData(const GameString& _Mesh, const GameString& _Path);

};

class GameSampler;
class GameCamera;
class GameMesh;
class GameRenderMgr;
class GameMaterial;
class GameRender : public GameTransform
{
public:
	friend GameRenderMgr;
	friend GameRenderData;

private:
	int m_Order;

public:
	std::vector<S_Ptr<GameRenderData>> m_RenderList;

public:
	GameRenderData* CreateRenderData(const GameString& _MeshName, const GameString& _Material);
	GameRenderData* CreateRenderData(const GameString& _MeshName, const GameString& _Material, CTransformData& _TransData);

public:
	virtual void Init(unsigned int _Order = 0);
	virtual void RenderUpdate(S_Ptr<GameCamera> _Cam);
	virtual void Render(S_Ptr<GameCamera> _Cam);

public:
	GameRender();
	~GameRender();
};

