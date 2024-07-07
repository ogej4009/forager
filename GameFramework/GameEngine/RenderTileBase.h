#pragma once
#include "GameRender.h"
#include "GameSprite.h"
#include <list>
#include <GameFile.h>

// 4Ãþ : UI
// 3Ãþ : ¿ÀºêÁ§Æ®(ÇÃ·¹ÀÌ¾î and ³ª¹«)
// 2Ãþ : Å¸ÀÏ
// 1Ãþ : ¹°
// 0Ãþ : Å¸ÀÏ º¿

class RenderTileSub;
class RenderTileBase : public GameRender
{
public:
	friend RenderTileSub;

public:
	class CKEY
	{
	public:
		union
		{
			struct
			{
				int X;
				int Y;
			};

			__int64 TileKey;
		};

		CKEY& operator+=(const CKEY& _Other)
		{
			X += _Other.X;
			Y += _Other.Y;
			return *this;
		}

		CKEY() : X(0), Y(0)
		{
		}

		CKEY(int _X, int _Y) : X(_X), Y(_Y)
		{

		}


	};


	enum TILEDIR
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


	struct TILEINDEXDATA
	{
	public:
		bool Check[8];
		int Index;
	};

	static CKEY ArrCheck[8];
	static TILEDIR ArrTILE4WAYDIR[4];
	static TILEINDEXDATA TileIndex[49];

	static bool IsMapWay;

private:
	class Tile
	{
	public:
		CKEY m_Key;
		CTransformData m_TransData;
		unsigned int m_Index;
		GameRenderData* RD;

	public:
		Tile(int _Index, GameRenderData* _RD) : RD(_RD), m_Index(_Index)
		{
		}
	};

private:
	S_Ptr<GameSprite> m_Sprite;
	CVector m_Color;

public:
	/*static*/ std::map<__int64, Tile*> m_AllTile;
	std::list<Tile*> m_AllTileList;

public:
	void Sprite(const GameString& _Name)
	{
		m_Sprite = GameSprite::Find(_Name);

		if (nullptr == m_Sprite)
		{
			CodeEmbeddedErrorDetection;
		}
	}

	S_Ptr<GameSprite> Sprite() { return m_Sprite; }

	CKEY KCreateKey(int _X, int _Y)
	{
		CKEY Key = CKEY(_X, _Y);
		return Key;
	}

	_int64 CreateKey(int _X, int _Y)
	{
		CKEY Key = KCreateKey(_X, _Y);
		return Key.TileKey;
	}

	bool IsTile(CVector _Pos)
	{
		if (m_AllTile.end() != m_AllTile.find(CreateKey((int)std::roundf(_Pos.x), (int)std::roundf(_Pos.y))))
		{
			return true;
		}
		return false;
	}

	void CreateTile(CVector _Pos, unsigned int _Index = 0)
	{
		CreateTile((int)std::roundf(_Pos.x), (int)std::roundf(_Pos.y), _Index);
	}

	void CreateTile(int _X, int _Y, unsigned int _Index = -1)
	{
		CreateTile(CreateKey(_X, _Y), _Index = -1);
	}

	void CreateTile(__int64 _Key, unsigned int _Index = -1)
	{
		__int64 Key = _Key;

		if (m_AllTile.end() != m_AllTile.find(Key))
		{
			return;
		}

		Tile* NewTile = new Tile(0, nullptr);
		NewTile->m_Key.TileKey = Key;
		m_AllTile.insert(std::map<__int64, Tile*>::value_type(Key, NewTile));
		m_AllTileList.push_back(NewTile);

		GameRenderData* RD = CreateRenderData(L"RECT2D", L"SPRITE2D", NewTile->m_TransData);
		RD->SMP(L"LSMP", L"LSMP");
		RD->SMP(L"PSMP", L"PSMP");
		RD->CB(L"CB_COLOR", m_Color, true);
		RD->TEX("TEX2D", m_Sprite->Tex());
		NewTile->RD = RD;

		// »õ·Î¸¸µé¾îÁø Å¸ÀÏ ÀÎµ¦½º Ã¼Å©
		if (-1 == _Index)
		{
			CalTileTest(Key);

			CKEY CheckKey;
			for (size_t i = 0; i < MAX; i++)
			{

				CheckKey.TileKey = Key;
				CheckKey += ArrCheck[i];

				CalTileTest(CheckKey.TileKey);
			}
		}
		else {
			NewTile->m_Index = _Index;
			NewTile->RD->CB(L"CB_CUT", m_Sprite->CutData(NewTile->m_Index));
		}

	}

	void Render(S_Ptr<GameCamera> _Cam) override;
	void CalTileTest(__int64 Key);
	void Save(FILE* _GameFile);
	void Load(FILE* _GameFile);
	void Clear();

public:
	RenderTileBase();
	~RenderTileBase();
};
