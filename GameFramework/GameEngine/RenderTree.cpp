#include "RenderTree.h"
#include <LogicData.h>
#include "GameCol.h"
#include "RenderMisc.h"


std::list<S_Ptr<GameActor>> RenderTree::g_DropItemObjList;		//  IsDeath일 때
std::list<S_Ptr<DropItem>> RenderTree::g_DropItemList;
bool RenderTree::g_IsLoad;

RenderTree::RenderTree()
	: m_Color(CVector::WHITE)
{
}

RenderTree::~RenderTree()
{
	Clear();
}

void RenderTree::Render(S_Ptr<GameCamera> _Cam)
{
	GameTransform::Update();
	GameTransform::CalTransData(_Cam);

	Render(_Cam, g_IsLoad);

	// 각 타일의 트랜스 데이터를 업데이트 할 것이다.

	for (auto& RD : m_RenderList)
	{
		if (false == RD->IsUpdate())
		{
			continue;
		}

		RD->Render();
	}
}

void RenderTree::Render(S_Ptr<GameCamera> _Cam, bool g_IsLoad)
{
	CVector TilePos;

	if (g_IsLoad == false) // Tool 상태
	{
		for (auto& Tile : TileObjList)
		{
			Tile->m_TransData.W = CREFWW();

			TilePos.x = (Tile->m_TransData.W.ArrVec[3].x + (float)(Tile->m_Key.X * Tile->m_TransData.W.ArrVec[0].x)) / 2;
			TilePos.y = (Tile->m_TransData.W.ArrVec[3].y + (float)(Tile->m_Key.Y * Tile->m_TransData.W.ArrVec[1].y)) / 2 + 0.5f;
			TilePos.z = Tile->m_TransData.W.ArrVec[3].z;

			Tile->m_TransData.W.ArrVec[3] = TilePos;
			Tile->m_TransData.V = _Cam->MatView();
			Tile->m_TransData.P = _Cam->MatProj();
			Tile->m_TransData.WV = m_Tree->m_TransData.W * m_Tree->m_TransData.V;
			Tile->m_TransData.VP = _Cam->MatViewProj();
			Tile->m_TransData.WVP = Tile->m_TransData.W * Tile->m_TransData.V * Tile->m_TransData.P;
			Tile->m_TransData.AllTP();

		}
	}
	else if (g_IsLoad == true) // Load 상태
	{
		for (auto& Tile : TileObjList)
		{
			Tile->m_TransData.W = CREFWW();

			TilePos.x = (Tile->m_TransData.W.ArrVec[3].x + (float)(Tile->m_Key.X * Tile->m_TransData.W.ArrVec[0].x)) / 3;
			TilePos.y = (Tile->m_TransData.W.ArrVec[3].y + (float)(Tile->m_Key.Y * Tile->m_TransData.W.ArrVec[1].y)) / 3 + 0.5f;
			TilePos.z = Tile->m_TransData.W.ArrVec[3].z;

			Tile->m_TransData.W.ArrVec[3] = TilePos;
			Tile->m_TransData.V = _Cam->MatView();
			Tile->m_TransData.P = _Cam->MatProj();
			Tile->m_TransData.WV = m_Tree->m_TransData.W * m_Tree->m_TransData.V;
			Tile->m_TransData.VP = _Cam->MatViewProj();
			Tile->m_TransData.WVP = Tile->m_TransData.W * Tile->m_TransData.V * Tile->m_TransData.P;
			Tile->m_TransData.AllTP();

		}
	}
}

void RenderTree::Save(FILE* _GameFile)
{
	UINT Size = (UINT)TileObjMap.size();
	fwrite(&Size, sizeof(UINT), 1, _GameFile);

	for (auto& _Tile : TileObjMap)
	{
		fwrite(&(_Tile.second->m_Key.TileKey), sizeof(__int64), 1, _GameFile);
		fwrite(&(_Tile.second->m_Index), sizeof(unsigned int), 1, _GameFile);
	}
}

void RenderTree::ObjLoad(FILE* _GameFile, S_Ptr<GameScene> _Scene)
{

}

void RenderTree::Load(FILE* _GameFile, S_Ptr<GameScene> _Scene)
{
	g_IsLoad = true;

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
		S_Ptr<GameCol> m_Col = PTR->AddCom<GameCol>(GameCol::COLTYPE::OBBRECT, (UINT)COL_ORDER::CO_MISC);
		//m_Col->Trans()->LPOS({ m_Pos.x,m_Pos.y + 1.0f,1.0f });
		//m_Col->Trans()->LSCALE({ 1.0f,1.0f,1.0f });
		S_Ptr<RenderTree> TR = PTR->AddCom<RenderTree>();

		TR->Trans()->LPOS(Pos);
		TR->Trans()->LSCALE({ 2.0f,2.0f,1.0f });

		TR->Sprite(L"Tree.png");
		TR->CreateTileObj(Key, Index);

		g_DropItemObjList.push_back(PTR);

		// DROPITEM
		S_Ptr<GameActor> DROPITEM = _Scene->CreateActor();
		S_Ptr<DropItem> DROP = DROPITEM->AddCom<DropItem>();
		DROP->SetItem(L"Tree.png", Index);
		DROP->SetDropPos(Pos);
		DROP->SetListCount(i);
		DROP->SetROBJ(TILEOBJ::T_TREE);
		g_DropItemList.push_back(DROP);

		PTR->Trans()->LPOS(Pos);
	}
	/*
		Sprite(L"Tree.png");

		UINT Count;
		fread(&Count, sizeof(UINT), 1, _GameFile);

		CTileRender::CKEY _LoadKey;
		unsigned int Index;

		for (UINT i = 0; i < Count; i++)
		{
			fread(&_LoadKey, sizeof(__int64), 1, _GameFile);
			fread(&Index, sizeof(unsigned int), 1, _GameFile);
		}
	*/
}

void RenderTree::Clear()
{
	for (auto& Tile : TileObjList)
	{
		Tile->RD->Death();
		delete Tile;
	}

	TileObjList.clear();
	TileObjMap.clear();
}

