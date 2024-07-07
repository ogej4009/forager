#pragma once
#include "GameRender.h"
#include "GameScene.h"
#include "GameActor.h"
#include "RenderTileBase.h"
#include "DropItem.h"

class RenderMisc : public GameRender
{
public:	
	static std::list<S_Ptr<GameActor>> g_DropItemObjList;	
	static std::list<S_Ptr<DropItem>> DROPITEMLIST;	

private:
	RenderTileBase::CKEY BKey; // TileBKey

public:
	static bool g_IsLoad;

private:
	class TileObj
	{
	public:
		RenderTileBase::CKEY m_Key;
		CTransformData m_TransData;
		unsigned int m_Index;
		GameRenderData* RD;
		TileObj(int _Index, GameRenderData* _RD) : RD(_RD), m_Index(_Index)
		{
		}
	};

private:
	S_Ptr<GameSprite> m_Sprite;
	CVector m_Color;
	std::map<__int64, TileObj*> m_AllObj;
	std::list<TileObj*> m_AllObjList;

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

	__int64 CreateKey(int _X, int _Y)
	{
		BKey = RenderTileBase::CKEY(_X, _Y);
		return BKey.TileKey;
	}

	void CreateObj(CVector _Pos, unsigned int _Index = 0)
	{
		CreateObj((int)std::roundf(_Pos.x), (int)std::roundf(_Pos.y), _Index);
	}

	void CreateObj(int _X, int _Y, unsigned int _Index = 0)
	{
		CreateObj(CreateKey(_X, _Y), _Index);
	}

	void CreateObj(__int64 _Key, unsigned int _Index = 0)
	{
		__int64 Key = _Key;

		if (m_AllObj.end() != m_AllObj.find(Key))
		{
			return;
		}

		TileObj* NewTile = new TileObj(0, nullptr);
		NewTile->m_Key.TileKey = Key;

		m_AllObj.insert(std::map<__int64, TileObj*>::value_type(Key, NewTile));
		m_AllObjList.push_back(NewTile);

		GameRenderData* RD = CreateRenderData(L"RECT2D", L"SPRITE2D", NewTile->m_TransData);
		RD->SMP(L"LSMP", L"LSMP");
		RD->SMP(L"PSMP", L"PSMP");
		RD->CB(L"CB_COLOR", m_Color, true);
		RD->TEX(L"TEX2D", m_Sprite->Tex());

		NewTile->RD = RD;
		NewTile->m_Index = _Index;
		NewTile->RD->CB(L"CB_CUT", m_Sprite->CutData(NewTile->m_Index));
	}

	void Render(S_Ptr<GameCamera> _Cam) override;
	void Render(S_Ptr<GameCamera> _Cam, bool _IsLoad);

	void Save(FILE* _GameFile);
	void Load(FILE* _GameFile, S_Ptr<GameScene> _Scene);

	void Clear();

public:
	RenderMisc();
	~RenderMisc();
};

