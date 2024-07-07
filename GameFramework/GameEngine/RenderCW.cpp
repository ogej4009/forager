#include "RenderCW.h"
#include <LogicData.h>
#include "GameCol.h"

bool RenderCW::g_IsLoad;

RenderCW::RenderCW()
	: m_Color(CVector::WHITE)
{
}

RenderCW::~RenderCW()
{
	Clear();
}

void RenderCW::Render(S_Ptr<GameCamera> _Cam)
{
	GameTransform::Update();
	GameTransform::CalTransData(_Cam);

	Render(_Cam, g_IsLoad);

	for (auto& RD : m_RenderList)
	{
		if (false == RD->IsUpdate())
		{
			continue;
		}

		RD->Render();
	}
}

void RenderCW::Render(S_Ptr<GameCamera> _Cam, bool _IsLoad)
{
	//CVEC4 TilePos;

	//if (_IsLoad == false)
	//{
	//	for (auto& Tile : m_AllWList)
	//	{
	//		Tile->m_TransData.W = CREFWW();

	//		TilePos.x = Tile->m_TransData.W.ArrVec[3].x + (float)(Tile->m_Key.X * Tile->m_TransData.W.ArrVec[0].x);
	//		TilePos.y = Tile->m_TransData.W.ArrVec[3].y + (float)(Tile->m_Key.Y * Tile->m_TransData.W.ArrVec[1].y);
	//		TilePos.z = Tile->m_TransData.W.ArrVec[3].z;

	//		Tile->m_TransData.W.ArrVec[3] = TilePos;
	//		Tile->m_TransData.V = _Cam->MatView();
	//		Tile->m_TransData.P = _Cam->MatProj();
	//		Tile->m_TransData.WV = Tile->m_TransData.W * Tile->m_TransData.V;
	//		Tile->m_TransData.VP = _Cam->MatViewProj();
	//		Tile->m_TransData.WVP = Tile->m_TransData.W * Tile->m_TransData.V * Tile->m_TransData.P;
	//		Tile->m_TransData.AllTP();

	//		// 각 타일의 트랜스 데이터를 업데이트 할것이다.
	//	}
	//}
	//else if (_IsLoad == true)
	//{
	//	for (auto& Tile : m_AllWList)
	//	{
	//		Tile->m_TransData.W = CREFWW();

	//		TilePos.x = Tile->m_TransData.W.ArrVec[3].x + (float)(Tile->m_Key.X * Tile->m_TransData.W.ArrVec[0].x) / 300;
	//		TilePos.y = Tile->m_TransData.W.ArrVec[3].y + (float)(Tile->m_Key.Y * Tile->m_TransData.W.ArrVec[1].y) / 300;
	//		TilePos.z = Tile->m_TransData.W.ArrVec[3].z;

	//		Tile->m_TransData.W.ArrVec[3] = TilePos;
	//		Tile->m_TransData.V = _Cam->MatView();
	//		Tile->m_TransData.P = _Cam->MatProj();
	//		Tile->m_TransData.WV = Tile->m_TransData.W * Tile->m_TransData.V;
	//		Tile->m_TransData.VP = _Cam->MatViewProj();
	//		Tile->m_TransData.WVP = Tile->m_TransData.W * Tile->m_TransData.V * Tile->m_TransData.P;
	//		Tile->m_TransData.AllTP();

	//		// 각 타일의 트랜스 데이터를 업데이트 할것이다.
	//	}
	//}
}

void RenderCW::Save(FILE* _GameFile)
{
	UINT Size = (UINT)m_Sprite->GetCGStrName().Size();
	fwrite(&Size, sizeof(UINT), 1, _GameFile);
	fwrite(m_Sprite->GetCGStrName().StrPtr(), sizeof(wchar_t) * Size, 1, _GameFile);

	Size = (UINT)m_AllW.size();
	fwrite(&Size, sizeof(UINT), 1, _GameFile);

	for (auto& _Tile : m_AllW)
	{
		fwrite(&(_Tile.second->m_Key.TileKey), sizeof(__int64), 1, _GameFile);
		fwrite(&(_Tile.second->m_Index), sizeof(unsigned int), 1, _GameFile);
	}
}

void RenderCW::Load(FILE* _GameFile, S_Ptr<GameScene> _Scene)
{
	Clear();
	g_IsLoad = true;

	static wchar_t szBuffer[255] = {};
	wmemset(szBuffer, L'\0', 255);

	UINT iLen = 0;
	fread(&iLen, sizeof(UINT), 1, _GameFile);
	fread(szBuffer, sizeof(wchar_t), iLen, _GameFile);

	std::wstring Str = szBuffer;

	UINT Count;
	fread(&Count, sizeof(UINT), 1, _GameFile);

	RenderTileBase::CKEY _LoadKey;
	unsigned int Index;

	for (UINT i = 0; i < Count; i++)
	{
		fread(&_LoadKey, sizeof(__int64), 1, _GameFile);
		fread(&Index, sizeof(unsigned int), 1, _GameFile);

		__int64 Key = _LoadKey.TileKey;

		CVector Pos = { (float)_LoadKey.X, (float)_LoadKey.Y, 1.0f };

		S_Ptr<GameActor> PTR = _Scene->CreateActor();
		PTR->Trans()->LSCALE({ 1.f,1.0f,1.0f });
		S_Ptr<RenderCW> TR = PTR->AddCom<RenderCW>();
		//S_Ptr<CWTLogic> WT = PTR->AddCom<CWTLogic>();
		TR->Sprite(Str);
		TR->CreateObj(Key, Index);

		PTR->Trans()->LPOS(Pos);
	}
}

void RenderCW::Clear()
{
	std::map<__int64, TileW*>::iterator Start = m_AllW.begin();
	std::map<__int64, TileW*>::iterator End = m_AllW.end();

	for (; Start != End; ++Start)
	{
		Start->second->RD->Death();
		delete Start->second;
	}
	m_AllWList.clear();
	m_AllW.clear();
}
