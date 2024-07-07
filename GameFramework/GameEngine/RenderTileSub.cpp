#include "RenderTileSub.h"



RenderTileBase::CKEY RenderTileSub::ArrCheck[8] = {
	RenderTileBase::CKEY(-1, 0),
	RenderTileBase::CKEY(-1, 1),
	RenderTileBase::CKEY(0, 1),
	RenderTileBase::CKEY(1, 1),
	RenderTileBase::CKEY(1, 0),
	RenderTileBase::CKEY(1, -1),
	RenderTileBase::CKEY(0, -1),
	RenderTileBase::CKEY(-1, -1),
};

RenderTileSub::TILEBDIR ArrTILEB4WAYDIR[4] = {
	RenderTileSub::TILEBDIR::L,
	RenderTileSub::TILEBDIR::R,
	RenderTileSub::TILEBDIR::T,
	RenderTileSub::TILEBDIR::B
};


// 양쪽에 TileB가 없다. Index(44)
// Left에 TileB가 있다. Index(3)
// Right에 TileB가 있다. Index(1)
// 양쪽에 TileB가 있다. Index(15)

// Left에 Tile이 있다. Index(3)
// Right에 Tile이 있다. Index(1)
// 양쪽에 Tile이 있다. Index(15)
RenderTileSub::TILEBINDEXDATA RenderTileSub::TileIndex[30] = {

	//false, false, false, false, true , false, false, false
	//L,     LT,    T,     RT,    R,     RB,    B,     LB

	{{true/**/, false, false, false, false, false, false, false}, 3}, // Left에 TileB가 있다.
	{{true/**/, true, false, false, false, false, false, false}, 3}, // LT
	{{true/**/, false, false, true, false, false, false, false}, 3}, // RT
	{{true/**/, false, true, false, false, false, false, false}, 3}, // T
	{{true/**/, true, false, true, false, false, false, false}, 3}, // LT, RT
	{{true/**/, true, true, false, false, false, false, false}, 3}, // LT, T
	{{true/**/, false, true, true, false, false, false, false}, 3}, // T, RT
	{{true/**/, true, true, true, false, false, false, false}, 3}, // LT, T, RT
	{{true/**/, false, false, false, false, false, false, true}, 3}, // LB
	{{true/**/, false, false, false, false, false, false, false}, 3},


	{{true/**/, false, false, false, true/**/, false, false, false}, 15}, // 양쪽에 TileB가 있다. Index(15)
	{{true/**/, false, true, false, true/**/, false, false, false}, 15}, // T
	{{true/**/, false, true, true, true/**/, false, false, false}, 15}, // T, RT
	{{true/**/, true, true, false, true/**/, false, false, false}, 15}, // LT, T
	{{true/**/, true, true, true, true/**/, false, false, false}, 15}, // LT, T, RT
	{{true/**/, false, false, false, true/**/, true, false, true}, 15},


	{{false, false, false, false, true/**/, false, false, false}, 1}, // Right에  TileB가 있다.
	{{false, false, false, true, true/**/, false, false, false}, 1}, // RT
	{{false, true, false, false, true/**/, false, false, false}, 1}, // LT
	{{false, true, true, true, true/**/, false, false, false}, 1}, // LT, RT
	{{false, false, false, false, true/**/, true, false, false}, 1}, // RB
	{{false, false, false, false, true/**/, false, false, true}, 1}, // LB
	{{false, false, false, false, true/**/, true, false, true}, 1}, // RB, LB
	{{false, false, true, false, true/**/, false, false, false}, 1}, // T
	{{false, true, true, false, true/**/, false, false, false}, 1}, // LT, T
	{{false, false, true, true, true/**/, false, false, false}, 1}, // T, RT


	{{false, false, false, false, false, false, false, false}, 44}, // 양쪽에 TileB가 없다. 
	{{false, false, true, false, false, false, false, false}, 44}, // T
	{{false, true, false, false, false, false, false, false}, 44}, // LT
	{{false, false, false, true, false, false, false, false}, 44}, // RT

};

RenderTileSub::RenderTileSub()
	: m_Color(CVector::WHITE)
{
}

RenderTileSub::~RenderTileSub()
{
	Clear();
}

void RenderTileSub::Render(S_Ptr<GameCamera> _Cam)
{
	GameTransform::Update();
	GameTransform::CalTransData(_Cam);

	CVector TilePos;

	for (auto& Tile : m_AllTileBList)
	{
		Tile->m_TransData.W = CREFWW();

		TilePos.x = Tile->m_TransData.W.ArrVec[3].x + (float)(Tile->m_Key.X * Tile->m_TransData.W.ArrVec[0].x);
		TilePos.y = Tile->m_TransData.W.ArrVec[3].y + (float)(Tile->m_Key.Y * Tile->m_TransData.W.ArrVec[1].y);
		TilePos.z = Tile->m_TransData.W.ArrVec[3].z;

		Tile->m_TransData.W.ArrVec[3] = TilePos;

		Tile->m_TransData.W.Arr2D[0][0] *= 1.01F;
		Tile->m_TransData.W.Arr2D[1][1] *= 1.01F;
		Tile->m_TransData.W.Arr2D[2][2] *= 1.01F;
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

void RenderTileSub::CalTileBTest(__int64 Key)
{
	std::map<__int64, TileB*>::iterator FindIter = m_AllTileB.find(Key);

	if (m_AllTileB.end() == FindIter)
	{
		return;
	}

	RenderTileBase::CKEY CheckKey;
	CheckKey.TileKey = Key;

	bool ArrDirCheck[TILEBDIR::MAX] = { 0, };
	for (size_t i = 0; i < TILEBDIR::MAX; i++)
	{
		CheckKey.TileKey = Key;
		CheckKey += ArrCheck[i];

		if (m_AllTileB.end() != m_AllTileB.find(CheckKey.TileKey))
		{
			if (i == TILEBDIR::LB || i == TILEBDIR::RB
				|| i == TILEBDIR::RT || i == TILEBDIR::LT)
			{
				RenderTileBase::CKEY Pos1;
				RenderTileBase::CKEY Pos2;

				if (i == TILEBDIR::LB)
				{
					Pos1.TileKey = Key;
					Pos1 += ArrCheck[TILEBDIR::L];
					Pos2.TileKey = Key;
					Pos2 += ArrCheck[TILEBDIR::B];
				}
				if (i == TILEBDIR::RB)
				{
					Pos1.TileKey = Key;
					Pos1 += ArrCheck[TILEBDIR::R];
					Pos2.TileKey = Key;
					Pos2 += ArrCheck[TILEBDIR::B];
				}
				if (i == TILEBDIR::LT)
				{
					Pos1.TileKey = Key;
					Pos1 += ArrCheck[TILEBDIR::L];
					Pos2.TileKey = Key;
					Pos2 += ArrCheck[TILEBDIR::T];
				}
				if (i == TILEBDIR::RT)
				{
					Pos1.TileKey = Key;
					Pos1 += ArrCheck[TILEBDIR::R];
					Pos2.TileKey = Key;
					Pos2 += ArrCheck[TILEBDIR::T];
				}


				// 서로간의 틈새 타일들이 무조건 2개 일수밖에 없다.
				// 2곳에 타일이 다 있을때 고려해야할 타일이다.
				if ((m_AllTileB.end() != m_AllTileB.find(Pos1.TileKey)) &&
					(m_AllTileB.end() != m_AllTileB.find(Pos2.TileKey)))
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

	FindIter->second->m_Index = 44;
	FindIter->second->RD->CB(L"CB_CUT", m_Sprite->CutData(44));
	return;
}

void RenderTileSub::Save(FILE* _GameFile)
{
	UINT Size = (UINT)m_Sprite->GetCGStrName().Size();
	fwrite(&Size, sizeof(UINT), 1, _GameFile);
	fwrite(m_Sprite->GetCGStrName().StrPtr(), sizeof(wchar_t) * Size, 1, _GameFile);

	Size = (int)m_AllTileB.size();
	fwrite(&Size, sizeof(int), 1, _GameFile);

	for (auto& _Tile : m_AllTileB)
	{
		fwrite(&(_Tile.second->m_Key.TileKey), sizeof(__int64), 1, _GameFile);
		fwrite(&(_Tile.second->m_Index), sizeof(unsigned int), 1, _GameFile);
	}
}

void RenderTileSub::Load(FILE* _GameFile)
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

	RenderTileBase::CKEY _LoadKey;
	unsigned int Index;

	for (UINT i = 0; i < Count; i++)
	{
		fread(&_LoadKey, sizeof(__int64), 1, _GameFile);
		fread(&Index, sizeof(unsigned int), 1, _GameFile);

		CreateTileB(_LoadKey.TileKey, Index);
	}
}

void RenderTileSub::Clear()
{
	std::map<__int64, TileB*>::iterator Start = m_AllTileB.begin();
	std::map<__int64, TileB*>::iterator End = m_AllTileB.end();

	for (; Start != End; ++Start)
	{
		Start->second->RD->Death();
		delete Start->second;
	}
	m_AllTileBList.clear();
	m_AllTileB.clear();
}
