#include "GameRender.h"
#include "GameActor.h"
#include "GameScene.h"
#include "GameCamera.h"

GameRenderData::GameRenderData(const GameString& _Mesh, const GameString& _Path)
	: m_DrawMode(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	m_Mesh = GameMesh::Find(_Mesh);
	m_Material = GameMaterial::Find(_Path);
}

void GameRenderData::MaterialInit()
{
	for (size_t i = 0; i < GameShader::SHADER_TYPE::ST_MAX; ++i)
	{
		GameShader* SH = m_Material->Shader(i);

		if (nullptr == SH)
		{
			continue;
		}

		for (auto& Var : SH->m_CB)
		{
			CBData CD = CBData();
			CD.Slot = Var.second->Slot();
			CD.CB = Var.second;

			if (true == CD.CB->Check<CTransformData>())
			{
				CD.m_IsLink = true;
				CD.Size = sizeof(CTransformData);
				CD.Data = m_pData;
			}

			CBRes[(GameShader::SHADER_TYPE)i].insert(std::map<GameString, CBData>::value_type(Var.first, CD));


		}

		for (auto& Var : SH->m_TEX)
		{
			TexData TD = TexData();
			TD.Slot = Var.second;
			TexRes[(GameShader::SHADER_TYPE)i].insert(std::map<GameString, TexData>::value_type(Var.first, TD));
		}

		for (auto& Var : SH->m_SMP)
		{
			SMPData SD = SMPData();
			SD.Slot = Var.second;
			SmpRes[(GameShader::SHADER_TYPE)i].insert(std::map<GameString, SMPData>::value_type(Var.first, SD));
		}

	}

}

S_Ptr<GameMaterial> GameRenderData::Material()
{
	if (false == m_Material->IsClone())
	{
		m_Material = m_Material->Clone();
	}

	return m_Material;
}


void GameRenderData::CBDataCreate(const GameString& _Name, void* _Data, bool _bLink, GameShader::SHADER_TYPE _Type)
{
	if (_Type != GameShader::SHADER_TYPE::ST_MAX)
	{
		if (true == _bLink)
		{
			CBRes[_Type][_Name].Reset();
			CBRes[_Type][_Name].m_IsLink = _bLink;
			CBRes[_Type][_Name].Size = CBRes[_Type][_Name].CB->BufferDesc().ByteWidth;
			CBRes[_Type][_Name].Data = _Data;
		}
		else {

			// CbRes[_Type][_Name].Reset();
			unsigned int BSize = CBRes[_Type][_Name].CB->BufferDesc().ByteWidth;
			if (nullptr == CBRes[_Type][_Name].Data)
			{
				CBRes[_Type][_Name].Data = new char[BSize];
				CBRes[_Type][_Name].Size = CBRes[_Type][_Name].CB->BufferDesc().ByteWidth;
			}
			memcpy_s(CBRes[_Type][_Name].Data, BSize, _Data, BSize);
		}
	}
	else
	{
		for (size_t i = 0; i < GameShader::SHADER_TYPE::ST_MAX; ++i)
		{
			std::map<GameShader::SHADER_TYPE, std::map<GameString, CBData>>::iterator CBIter = CBRes.find((GameShader::SHADER_TYPE)i);

			if (CBIter == CBRes.end())
			{
				continue;
			}

			std::map<GameString, CBData>::iterator CBFindIter = CBIter->second.find(_Name);

			if (CBFindIter == CBIter->second.end())
			{
				continue;
			}

			if (true == _bLink)
			{
				CBFindIter->second.Reset();
				CBFindIter->second.Size = CBFindIter->second.CB->BufferDesc().ByteWidth;
				CBFindIter->second.m_IsLink = _bLink;
				CBFindIter->second.Data = _Data;
			}
			else
			{
				unsigned int BSize = CBFindIter->second.CB->BufferDesc().ByteWidth;
				if (nullptr == CBFindIter->second.Data)
				{
					CBFindIter->second.Size = CBFindIter->second.CB->BufferDesc().ByteWidth;
					CBFindIter->second.Data = new char[BSize];
				}
				memcpy_s(CBFindIter->second.Data, BSize, _Data, BSize);
			}
		}

	}

}

void GameRenderData::SMP(const GameString& _Name, const GameString& _SmpName, GameShader::SHADER_TYPE _Type)
{
	GameSampler* Res = GameSampler::Find(_SmpName);

	if (nullptr == Res)
	{
		CodeEmbeddedErrorDetection;
	}

	if (_Type != GameShader::SHADER_TYPE::ST_MAX)
	{
		SmpRes[_Type][_Name].Smp = Res;
	}
	else
	{
		for (size_t i = 0; i < GameShader::SHADER_TYPE::ST_MAX; ++i)
		{

			std::map<GameShader::SHADER_TYPE, std::map<GameString, SMPData>>::iterator SmpIter = SmpRes.find((GameShader::SHADER_TYPE)i);

			if (SmpIter == SmpRes.end())
			{
				continue;
			}

			std::map<GameString, SMPData>::iterator SmpFindIter = SmpIter->second.find(_Name);

			if (SmpFindIter == SmpIter->second.end())
			{
				continue;
			}

			SmpFindIter->second.Smp = Res;


		}
	}


}





void GameRenderData::TEX(const GameString& _Name, const GameString& _TexName, GameShader::SHADER_TYPE _Type)
{

	GameTexture* Res = GameTexture::Find(_Name);

	if (nullptr == Res)
	{
		CodeEmbeddedErrorDetection;
	}

	TEX(_Name, Res, _Type);

}

void GameRenderData::TEX(const GameString& _Name, S_Ptr<GameTexture> _Tex, GameShader::SHADER_TYPE _Type)
{
	if (_Type != GameShader::SHADER_TYPE::ST_MAX)
	{
		TexRes[_Type][_Name].Tex = _Tex;
	}
	else
	{
		for (size_t i = 0; i < GameShader::SHADER_TYPE::ST_MAX; ++i)
		{

			std::map<GameShader::SHADER_TYPE, std::map<GameString, TexData>>::iterator TexIter = TexRes.find((GameShader::SHADER_TYPE)i);

			if (TexIter == TexRes.end())
			{
				continue;
			}

			std::map<GameString, TexData>::iterator TexFindIter = TexIter->second.find(_Name);

			if (TexFindIter == TexIter->second.end())
			{
				continue;
			}

			TexFindIter->second.Tex = _Tex;


		}
	}
}




void GameRenderData::Render()
{
	m_Mesh->SettingVB();
	m_Mesh->SettingIB();
	m_Material->Setting();

	GameDevice::MainContext()->IASetPrimitiveTopology(m_DrawMode);

	for (auto& Var : CBRes)
	{
		for (auto& CBData : Var.second)
		{
			if (nullptr == CBData.second.CB)
			{
				CodeEmbeddedErrorDetection;
			}

			CBData.second.CB->SettingData(CBData.second.Data, CBData.second.Size);
			CBData.second.CB->Setting();

		}

	}

	for (auto& Var : TexRes)
	{
		for (auto& TexData : Var.second)
		{
			if (nullptr == TexData.second.Tex)
			{
				CodeEmbeddedErrorDetection;
			}

			TexData.second.Tex->Setting(Var.first, TexData.second.Slot);

		}
	}

	for (auto& Var : SmpRes)
	{
		for (auto& SmpData : Var.second)
		{
			if (nullptr == SmpData.second.Smp)
			{
				CodeEmbeddedErrorDetection;
			}

			SmpData.second.Smp->Setting(Var.first, SmpData.second.Slot);

		}
	}

	m_Mesh->RenderIndexed(0);

}


///////////////////////////////////////////////////// Render

GameRender::GameRender()
	: m_Order(0)
{
}

GameRender::~GameRender()
{
}

GameRenderData* GameRender::CreateRenderData(const GameString& _MeshName, const GameString& _Material)
{
	GameRenderData* RD = new GameRenderData(_MeshName, _Material);


	if (nullptr == RD->m_Mesh)
	{
		CodeEmbeddedErrorDetection;
	}

	if (nullptr == RD->m_Material)
	{
		CodeEmbeddedErrorDetection;
	}

	RD->m_pData = &m_TransData;
	RD->MaterialInit();
	m_RenderList.push_back(RD);

	return m_RenderList[m_RenderList.size() - 1];
}

GameRenderData* GameRender::CreateRenderData(const GameString& _MeshName, const GameString& _Material, CTransformData& _TransData)
{
	GameRenderData* RD = new GameRenderData(_MeshName, _Material);

	// 이때 저 데이터는 다 만들어져야 한다.
	if (nullptr == RD->m_Mesh)
	{
		CodeEmbeddedErrorDetection;
	}

	if (nullptr == RD->m_Material)
	{
		CodeEmbeddedErrorDetection;
	}

	RD->m_pData = &_TransData;
	RD->MaterialInit();
	m_RenderList.push_back(RD);

	return m_RenderList[m_RenderList.size() - 1];
}

void GameRender::Init(unsigned int _Order)
{
	m_Order = _Order;

	if (nullptr == Actor()->Scene())
	{
		CodeEmbeddedErrorDetection;
	}

	Parent(Actor()->Trans());

	Actor()->Scene()->RENDERMGR.PushRender(this);

}

void GameRender::RenderUpdate(S_Ptr<GameCamera> _Cam)
{
}

void GameRender::Render(S_Ptr<GameCamera> _Cam)
{
	GameTransform::Update();
	GameTransform::CalTransData(_Cam);

	for (auto& RD : m_RenderList)
	{
		RD->Render();
	}
}
