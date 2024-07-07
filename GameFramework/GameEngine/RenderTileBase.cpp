#include "RenderTileBase.h"

#include "GameCamera.h"
#include <GameFile.h>
#include "GameScene.h"
#include "GameCol.h"

#include <LogicData.h>

RenderTileBase::CKEY RenderTileBase::ArrCheck[8] = {
	RenderTileBase::CKEY(-1, 0),
	RenderTileBase::CKEY(-1, 1),
	RenderTileBase::CKEY(0, 1),
	RenderTileBase::CKEY(1, 1),
	RenderTileBase::CKEY(1, 0),
	RenderTileBase::CKEY(1, -1),
	RenderTileBase::CKEY(0, -1),
	RenderTileBase::CKEY(-1, -1),
};

RenderTileBase::TILEDIR RenderTileBase::ArrTILE4WAYDIR[4] = {
	RenderTileBase::TILEDIR::L,
	RenderTileBase::TILEDIR::R,
	RenderTileBase::TILEDIR::T,
	RenderTileBase::TILEDIR::B
};

RenderTileBase::TILEINDEXDATA RenderTileBase::TileIndex[49] =
{
	//false, false, false, false, true , false, false, false
	//L,     LT,    T,     RT,    R,     RB,    B,     LB

	{{false, }, 0},
	{{false, false, false, false, true, false, false, false}, 1},
	{{false, false, false, false, false, false, true, false}, 2},
	{{true, false, false, false, false, false, false, false}, 3},
	{{false, false, true, false, true, false, false, false}, 4},
	{{false, false, false, false, true, false, true, false}, 5},
	{{true, false, false, false, false, false, true, false}, 6},
	{{true, false, true, false, false, false, false, false}, 7},
	{{false, false, true, true, true, false, false, false}, 8},
	{{false, false, false, false, true, true, true, false}, 9},
	{{true, false, false, false, false, false, true, true}, 10},
	{{true, true, true, false, false, false, false, false}, 11},
	{{false, false, true, false, true, false, true, false}, 12},
	{{true, false, false, false, true, false, true, false}, 13},
	{{true, false, true, false, false, false, true, false}, 14},
	{{true, false, true, false, true, false, false, false}, 15},
	{{false, false, true, true, true, false, true, false}, 16},
	{{false, false, true, false, true, true, true, false}, 17},
	{{false, false, true, true, true, true, true, false}, 18},
	{{true, false, false, false, true, true, true, false}, 19},
	{{true, false, false, false, true, false, true, true}, 20},
	{{true, false, false, false, true, true, true, true}, 21},
	{{true, false, true, false, false, false, true, true}, 22},
	{{true, true, true, false, false, false, true, false}, 23},
	{{true, true, true, false, false, false, true, true}, 24},
	{{true, false, true, true, true, false, false, false}, 25},
	{{true, true, true, false, true, false, false, false}, 26},
	{{true, true, true, true, true, false, false, false}, 27},
	{{true, false, true, false, true, false, true, false}, 28},
	{{true, false, true, true, true, false, true, false}, 29},
	{{true, false, true, false, true, true, true, false}, 30},
	{{true, false, true, false, true, false, true, true}, 31},
	{{true, true, true, false, true, false, true, false}, 32},
	{{true, false, true, true, true, true, true, false}, 33},
	{{true, false, true, false, true, true, true, true}, 34},
	{{true, true, true, false, true, false, true, true}, 35},
	{{true, true, true, true, true, false, true, false}, 36},
	{{true, false, true, true, true, false, true, true}, 37},
	{{true, true, true, false, true, true, true, false}, 38},
	{{true, false, true, true, true, true, true, true}, 39},
	{{true, true, true, true, true, true, true, false}, 40},
	{{true, true, true, true, true, false, true, true}, 41},
	{{true, true, true, false, true, true, true, true}, 42},
	{{true, true, true, true, true, true, true, true}, 43},
	{{false, false, false, false, false, false, false, false}, 44},
	{{false, false, true, false, false, false, true, false}, 45},
	{{true, false, false, false, true, false, false, false}, 46},
	{{false, false, true, false, false, false, false, false}, 47},
	{{false, false, false, false, false, false, false, false}, 48},
};

//std::map<__int64, CTileRender::Tile*> CTileRender::m_AllTile;
bool RenderTileBase::IsMapWay;

RenderTileBase::RenderTileBase()
	: m_Color(CVector::ONE)
{
}

RenderTileBase::~RenderTileBase()
{
	Clear();
}

void RenderTileBase::Render(S_Ptr<GameCamera> _Cam)
{
	GameTransform::Update();
	GameTransform::CalTransData(_Cam);

	CVector TilePos;


	for (auto& Tile : m_AllTileList)
	{
		Tile->m_TransData.W = CREFWW();

		TilePos.x = Tile->m_TransData.W.ArrVec[3].x + (float)(Tile->m_Key.X * Tile->m_TransData.W.ArrVec[0].x);
		TilePos.y = Tile->m_TransData.W.ArrVec[3].y + (float)(Tile->m_Key.Y * Tile->m_TransData.W.ArrVec[1].y);
		TilePos.z = Tile->m_TransData.W.ArrVec[3].z;

		//Tile->m_TransData.W.Arr2D[0][0] *= 1.9F;
		//Tile->m_TransData.W.Arr2D[1][1] *= 1.9F;
		//Tile->m_TransData.W.Arr2D[2][2] *= 1.9F;

		Tile->m_TransData.W.ArrVec[3] = TilePos;
		Tile->m_TransData.V = _Cam->MatView();
		Tile->m_TransData.P = _Cam->MatProj();
		Tile->m_TransData.WV = Tile->m_TransData.W * Tile->m_TransData.V;
		Tile->m_TransData.VP = _Cam->MatViewProj();
		Tile->m_TransData.WVP = Tile->m_TransData.W * Tile->m_TransData.V * Tile->m_TransData.P;
		Tile->m_TransData.AllTP();

		// 각 타일의 트랜스 데이터를 업데이트 할것이다.
	}

	for (auto& RD : m_RenderList)
	{
		if (false == RD->IsUpdate())
		{
			continue;
		}

		RD->Render();
	}
}

void RenderTileBase::CalTileTest(__int64 Key)
{
	std::map<__int64, Tile*>::iterator FindIter = m_AllTile.find(Key);

	if (m_AllTile.end() == FindIter)
	{
		return;
	}

	CKEY CheckKey;
	CheckKey.TileKey = Key;

	bool ArrDirCheck[TILEDIR::MAX] = { 0, };
	for (size_t i = 0; i < TILEDIR::MAX; i++)
	{
		CheckKey.TileKey = Key;
		CheckKey += ArrCheck[i];

		if (m_AllTile.end() != m_AllTile.find(CheckKey.TileKey))
		{
			if (i == TILEDIR::LB || i == TILEDIR::RB
				|| i == TILEDIR::RT || i == TILEDIR::LT)
			{
				CKEY Pos1;
				CKEY Pos2;

				if (i == TILEDIR::LB)
				{
					Pos1.TileKey = Key;
					Pos1 += ArrCheck[TILEDIR::L];
					Pos2.TileKey = Key;
					Pos2 += ArrCheck[TILEDIR::B];
				}
				if (i == TILEDIR::RB)
				{
					Pos1.TileKey = Key;
					Pos1 += ArrCheck[TILEDIR::R];
					Pos2.TileKey = Key;
					Pos2 += ArrCheck[TILEDIR::B];
				}
				if (i == TILEDIR::LT)
				{
					Pos1.TileKey = Key;
					Pos1 += ArrCheck[TILEDIR::L];
					Pos2.TileKey = Key;
					Pos2 += ArrCheck[TILEDIR::T];
				}
				if (i == TILEDIR::RT)
				{
					Pos1.TileKey = Key;
					Pos1 += ArrCheck[TILEDIR::R];
					Pos2.TileKey = Key;
					Pos2 += ArrCheck[TILEDIR::T];
				}

				// 서로간의 틈새 타일들이 무조건 2개 일수밖에 없다.
				// 2곳에 타일이 다 있을때 고려해야할 타일이다.
				if ((m_AllTile.end() != m_AllTile.find(Pos1.TileKey)) &&
					(m_AllTile.end() != m_AllTile.find(Pos2.TileKey)))
				{
					ArrDirCheck[i] = true;
				}
			}
			else {
				ArrDirCheck[i] = true;
			}
		}
	}

	for (size_t i = 1; i < 48; i++)
	{
		int Test = memcmp(TileIndex[i].Check, ArrDirCheck, sizeof(__int64));

		if (0 == Test)
		{
			FindIter->second->m_Index = TileIndex[i].Index;
			FindIter->second->RD->CB(L"CB_CUT", m_Sprite->CutData(TileIndex[i].Index));
			return;
		}

	}

	FindIter->second->m_Index = 0;
	FindIter->second->RD->CB(L"CB_CUT", m_Sprite->CutData(0));
	return;
}

void RenderTileBase::Save(FILE* _GameFile)
{
	UINT Size = (UINT)m_Sprite->GetCGStrName().Size();
	fwrite(&Size, sizeof(UINT), 1, _GameFile);
	fwrite(m_Sprite->GetCGStrName().StrPtr(), sizeof(wchar_t) * Size, 1, _GameFile);

	Size = (int)m_AllTile.size();
	fwrite(&Size, sizeof(int), 1, _GameFile);

	for (auto& _Tile : m_AllTile)
	{
		fwrite(&(_Tile.second->m_Key.TileKey), sizeof(__int64), 1, _GameFile);
		fwrite(&(_Tile.second->m_Index), sizeof(unsigned int), 1, _GameFile);
	}
}

void RenderTileBase::Load(FILE* _GameFile)
{
	Clear();

	static wchar_t szBuffer[255] = {};
	wmemset(szBuffer, L'\0', 255);

	int iLen = 0;
	fread(&iLen, sizeof(int), 1, _GameFile);
	fread(szBuffer, sizeof(wchar_t), iLen, _GameFile);

	std::wstring Str = szBuffer;

	Sprite(Str);

	UINT Count;
	fread(&Count, sizeof(UINT), 1, _GameFile);

	CKEY _LoadKey;
	unsigned int Index;

	for (UINT i = 0; i < Count; i++)
	{
		fread(&_LoadKey, sizeof(__int64), 1, _GameFile);
		fread(&Index, sizeof(unsigned int), 1, _GameFile);

		CreateTile(_LoadKey.TileKey, Index);
	}
}

void RenderTileBase::Clear()
{
	std::map<__int64, Tile*>::iterator Start = m_AllTile.begin();
	std::map<__int64, Tile*>::iterator End = m_AllTile.end();

	for (; Start != End; ++Start)
	{
		Start->second->RD->Death();
		delete Start->second;
	}
	m_AllTileList.clear();
	m_AllTile.clear();
}
