#pragma once
#include "GameRender.h"
#include "RenderTileBase.h"
#include <map>
#include <GameFile.h>


class RenderTileBase;
class RenderTileSub :
	public GameRender
{
private:
	RenderTileBase::CKEY BKey; // TileBKey

public:
	// 양쪽에 TileB가 없다. Index(44)
	// Left에 TileB가 있다. Index(3)
	// Right에 TileB가 있다. Index(1)
	// 양쪽에 TileB가 있다. Index(15)

	// Left에 Tile이 있다. Index(3)
	// Right에 Tile이 있다. Index(1)
	// 양쪽에 Tile이 있다. Index(15)
	enum TILEBDIR
	{
		L,
		LT,
		T,
		RT,
		R,
		RB,
		B,
		LB,
		MAX,
	};

	struct TILEBINDEXDATA
	{
	public:
		bool Check[8];
		int Index;
	};

	static RenderTileBase::CKEY ArrCheck[8];
	static TILEBDIR ArrTILEB4WAYDIR[4];
	static TILEBINDEXDATA TileIndex[30];

private:
	class TileB
	{
	public:
		RenderTileBase::CKEY m_Key;
		CTransformData m_TransData;
		unsigned int m_Index;
		GameRenderData* RD;

		TileB(int _Index, GameRenderData* _RD) : RD(_RD), m_Index(_Index)
		{
		}
	};

private:
	S_Ptr<GameSprite> m_Sprite;
	CVector m_Color;
	std::map<__int64, TileB*> m_AllTileB;
	std::list<TileB*> m_AllTileBList;

public:
	void Sprite(const GameString& _Name) {
		m_Sprite = GameSprite::Find(_Name);

		if (nullptr == m_Sprite)
		{
			CodeEmbeddedErrorDetection;
		}
	}

	S_Ptr<GameSprite> Sprite() { return m_Sprite; }

	__int64 CreateKey(int _X, int _Y)
	{
		BKey = RenderTileBase::CKEY(_X, _Y - 1);
		return BKey.TileKey;
	}

	void CreateTileB(CVector _Pos, unsigned int _Index = 0)
	{
		CreateTileB((int)std::roundf(_Pos.x), (int)std::roundf(_Pos.y), _Index);
	}

	void CreateTileB(int _X, int _Y, unsigned int _Index = -1)
	{
		CreateTileB(CreateKey(_X, _Y), _Index = -1);
	}

	void CreateTileB(__int64 _Key, unsigned int _Index = -1)
	{
		__int64 Key = _Key;

		if (m_AllTileB.end() != m_AllTileB.find(Key))
		{
			return;
		}

		TileB* NewTile = new TileB(0, nullptr);
		NewTile->m_Key.TileKey = Key;

		m_AllTileB.insert(std::map<__int64, TileB*>::value_type(Key, NewTile));
		m_AllTileBList.push_back(NewTile);

		GameRenderData* RD = CreateRenderData(L"RECT2D", L"SPRITE2D", NewTile->m_TransData);
		RD->SMP(L"LSMP", L"LSMP");
		RD->SMP(L"PSMP", L"PSMP");
		RD->CB(L"CB_COLOR", m_Color, true);
		RD->TEX("TEX2D", m_Sprite->Tex());
		NewTile->RD = RD;

		// 새로만들어진 타일 인덱스 체크
		if (-1 == _Index)
		{
			// 새로 만들어진 타일
			CalTileBTest(Key);

			RenderTileBase::CKEY CheckKey;
			for (size_t i = 0; i < MAX; i++)
			{

				CheckKey.TileKey = Key;
				CheckKey += ArrCheck[i];

				// 이전에 만들어진 타일
				CalTileBTest(CheckKey.TileKey);
			}
		}
		else
		{
			NewTile->m_Index = _Index;
			NewTile->RD->CB(L"CB_CUT", m_Sprite->CutData(NewTile->m_Index));
		}

	}

	void Render(S_Ptr<GameCamera> _Cam) override;
	void CalTileBTest(__int64 Key);
	void Save(FILE* _GameFile);
	void Load(FILE* _GameFile);
	void Clear();

public:
	RenderTileSub();
	~RenderTileSub();
};

