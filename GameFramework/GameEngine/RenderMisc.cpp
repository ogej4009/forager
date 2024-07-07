#include "RenderMisc.h"
#include <LogicData.h>
#include "GameCol.h"


bool RenderMisc::g_IsLoad;
std::list<S_Ptr<GameActor>> RenderMisc::g_DropItemObjList;
std::list<S_Ptr<DropItem>> RenderMisc::DROPITEMLIST;

RenderMisc::RenderMisc()
	: m_Color(CVector::WHITE)
{
}

RenderMisc::~RenderMisc()
{
	Clear();
}

void RenderMisc::Render(S_Ptr<GameCamera> _Cam)
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

void RenderMisc::Render(S_Ptr<GameCamera> _Cam, bool _IsLoad)
{
	CVector TilePos;

	if (_IsLoad == false)
	{
		for (auto& Tile : m_AllObjList)
		{
			Tile->m_TransData.W = CREFWW();

			TilePos.x = Tile->m_TransData.W.ArrVec[3].x + (float)(Tile->m_Key.X * Tile->m_TransData.W.ArrVec[0].x);
			TilePos.y = Tile->m_TransData.W.ArrVec[3].y + (float)(Tile->m_Key.Y * Tile->m_TransData.W.ArrVec[1].y);
			TilePos.z = Tile->m_TransData.W.ArrVec[3].z;

			Tile->m_TransData.W.ArrVec[3] = TilePos;
			Tile->m_TransData.V = _Cam->MatView();
			Tile->m_TransData.P = _Cam->MatProj();
			Tile->m_TransData.WV = Tile->m_TransData.W * Tile->m_TransData.V;
			Tile->m_TransData.VP = _Cam->MatViewProj();
			Tile->m_TransData.WVP = Tile->m_TransData.W * Tile->m_TransData.V * Tile->m_TransData.P;
			Tile->m_TransData.AllTP();

			// 각 타일의 트랜스 데이터를 업데이트 할 것이다.
		}
	}
	else if (_IsLoad == true)
	{
		for (auto& Tile : m_AllObjList)
		{
			Tile->m_TransData.W = CREFWW();

			TilePos.x = Tile->m_TransData.W.ArrVec[3].x + (float)(Tile->m_Key.X * Tile->m_TransData.W.ArrVec[0].x) / 100;
			TilePos.y = Tile->m_TransData.W.ArrVec[3].y + (float)(Tile->m_Key.Y * Tile->m_TransData.W.ArrVec[1].y) / 100;
			TilePos.z = Tile->m_TransData.W.ArrVec[3].z;

			Tile->m_TransData.W.ArrVec[3] = TilePos;
			Tile->m_TransData.V = _Cam->MatView();
			Tile->m_TransData.P = _Cam->MatProj();
			Tile->m_TransData.WV = Tile->m_TransData.W * Tile->m_TransData.V;
			Tile->m_TransData.VP = _Cam->MatViewProj();
			Tile->m_TransData.WVP = Tile->m_TransData.W * Tile->m_TransData.V * Tile->m_TransData.P;
			Tile->m_TransData.AllTP();

			// 각 타일의 트랜스 데이터를 업데이트 할것이다.
		}
	}

}

void RenderMisc::Save(FILE* _GameFile)
{
	UINT Size = (UINT)m_Sprite->GetCGStrName().Size();
	fwrite(&Size, sizeof(UINT), 1, _GameFile);
	fwrite(m_Sprite->GetCGStrName().StrPtr(), sizeof(wchar_t) * Size, 1, _GameFile);

	Size = (UINT)m_AllObj.size();
	fwrite(&Size, sizeof(UINT), 1, _GameFile);

	for (auto& _Tile : m_AllObj)
	{
		fwrite(&(_Tile.second->m_Key.TileKey), sizeof(__int64), 1, _GameFile);
		fwrite(&(_Tile.second->m_Index), sizeof(unsigned int), 1, _GameFile);
	}
}

void RenderMisc::Clear()
{
	std::map<__int64, TileObj*>::iterator Start = m_AllObj.begin();
	std::map<__int64, TileObj*>::iterator End = m_AllObj.end();

	for (; Start != End; ++Start)
	{
		Start->second->RD->Death();
		delete Start->second;
	}
	m_AllObjList.clear();
	m_AllObj.clear();
}

void RenderMisc::Load(FILE* _GameFile, S_Ptr<GameScene> _Scene)
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

		// 오브젝트
		S_Ptr<GameActor> PTR = _Scene->CreateActor();
		PTR->Trans()->LSCALE({ 1.f,1.0f,1.0f });
		PTR->Trans()->LPOS(Pos);
		S_Ptr<GameCol> m_Col = PTR->AddCom<GameCol>(GameCol::COLTYPE::OBBRECT, (UINT)COL_ORDER::CO_MISC);
		S_Ptr<RenderMisc> TR = PTR->AddCom<RenderMisc>();
		TR->Sprite(Str);
		TR->CreateObj(Key, Index);
		g_DropItemObjList.push_back(PTR);

		// DROPITEM
		S_Ptr<GameActor> DROPITEM = _Scene->CreateActor();
		S_Ptr<DropItem> DROP = DROPITEM->AddCom<DropItem>();
		DROP->SetItem(Str, Index);
		DROP->SetDropPos(Pos);
		DROP->SetListCount(i);
		DROP->SetROBJ(TILEOBJ::T_OBJ);
		DROPITEMLIST.push_back(DROP);

	}
}

