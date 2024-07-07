#pragma once
#include "GameScene.h"
#include "GameActor.h"
#include "GameRender.h"
#include "RenderTileBase.h"
#include "DropItem.h"

class RenderTileBase;
class RenderTree : public GameRender
{
public:
	// ObjRender에서 DropItem관련                            // 이 두 리스트에 들어있는 순서가 같기 때문에
	static std::list<S_Ptr<GameActor>> g_DropItemObjList;		//  IsDeath일 때
	static std::list<S_Ptr<DropItem>> g_DropItemList;			// Update에 LPOS값을 DROPPOS로 한다.

private:
	RenderTileBase::CKEY ObjKey;

private:
	class TileTree
	{
	public:
		RenderTileBase::CKEY m_Key;
		CTransformData m_TransData;
		unsigned int m_Index;
		GameRenderData* RD;

		TileTree(int _Index, GameRenderData* _RD) : RD(_RD), m_Index(_Index)
		{
		}
	};

private:
	S_Ptr<GameSprite> m_Sprite;
	CVector m_Color;
	TileTree* m_Tree;

public:
	std::map<__int64, TileTree*> TileObjMap;
	std::list<TileTree*> TileObjList;
	static bool g_IsLoad;

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

	RenderTileBase::CKEY KEY()
	{
		return ObjKey;
	}

	__int64 CreateKey(int _X, int _Y)
	{
		RenderTileBase::CKEY Key = RenderTileBase::CKEY(_X, _Y);
		return Key.TileKey;
	}

	static RenderTileBase::CKEY CreateObjKey(int _X, int _Y)
	{
		RenderTileBase::CKEY Key = RenderTileBase::CKEY(_X, _Y);
		return Key;
	}

	void CreateTileObj(CVector _Pos, unsigned int _Index = 0)
	{
		CreateTileObj((int)std::roundf(_Pos.x), (int)std::roundf(_Pos.y), _Index);
	}

	void CreateTileObj(int _X, int _Y, unsigned int _Index = 0)
	{
		CreateTileObj(CreateKey(_X, _Y), _Index);
	}

	void CreateTileObj(__int64 _Key, unsigned int _Index = 0)
	{
		__int64 Key = _Key;

		if (TileObjMap.end() != TileObjMap.find(Key))
		{
			return;
		}

		m_Tree = new TileTree(0, nullptr);
		m_Tree->m_Key.TileKey = Key;

		TileObjMap.insert(std::map<__int64, TileTree*>::value_type(Key, m_Tree));
		TileObjList.push_back(m_Tree);

		GameRenderData* RD = CreateRenderData(L"RECT2D", L"SPRITE2D", m_Tree->m_TransData);
		RD->SMP(L"LSMP", L"LSMP");
		RD->SMP(L"PSMP", L"PSMP");
		RD->CB(L"CB_COLOR", m_Color, true);
		RD->TEX(L"TEX2D", m_Sprite->Tex());

		m_Tree->RD = RD;
		m_Tree->m_Index = _Index;
		m_Tree->RD->CB(L"CB_CUT", m_Sprite->CutData(m_Tree->m_Index));

		//size_t size = TileObjList.size();
	}

	void Render(S_Ptr<GameCamera> _Cam) override;
	void Render(S_Ptr<GameCamera> _Cam, bool g_IsLoad);
	void Save(FILE* _GameFile);
	void ObjLoad(FILE* _GameFile, S_Ptr<GameScene> _Scene);
	void Load(FILE* _GameFile, S_Ptr<GameScene> _Scene);
	void Clear();

public:
	RenderTree();
	~RenderTree();
};

