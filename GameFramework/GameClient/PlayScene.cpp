#include "PlayScene.h"
#include <LogicData.h>
#include <GameInput.h>
#include <GameActor.h>
#include <GameTransform.h>
#include <GameRender.h>
#include <GameCamera.h>
#include <GameCol.h>
#include <GameDirectory.h>
#include <GameSprRender.h>
#include <GameTexture.h>
#include <GameSprite.h>
#include <GameAni.h>
#include <GameFrameDebug.h>
#include <RenderTileBase.h>
#include <RenderTileSub.h>
#include <RenderTree.h>
#include <RenderMisc.h>
#include <RenderCW.h>
#include <Inventory.h>
#include <Item.h>
#include <MenuBar.h>
#include <DropItem.h>
#include "Hero.h"
#include "MainCam.h"
#include "Cursor.h"
#include "Slime.h"
#include "Boar.h"
#include "Skeleton.h"


S_Ptr<Hero> PlayScene::g_Hero;
S_Ptr<RenderTileBase> PlayScene::g_GroundTile;
bool PlayScene::g_IsUIOn;

PlayScene::PlayScene() {}
PlayScene::~PlayScene() {}

void PlayScene::Loading()
{
	GameInput::CreateKey(L"ESC", VK_ESCAPE);
	GameInput::CreateKey(L"DEBUG_ON", VK_F1);

	Scene()->COLMGR.Link((UINT)COL_ORDER::CO_PLAYER	, (UINT)COL_ORDER::CO_DROPITEM);
	Scene()->COLMGR.Link((UINT)COL_ORDER::CO_DROPITEM, (UINT)COL_ORDER::CO_PLAYER);
	Scene()->COLMGR.Link((UINT)COL_ORDER::CO_PLAYER	, (UINT)COL_ORDER::CO_MONSTER);
	Scene()->COLMGR.Link((UINT)COL_ORDER::CO_PLAYER	, (UINT)COL_ORDER::CO_MISC);
	Scene()->COLMGR.Link((UINT)COL_ORDER::CO_DROPITEM, (UINT)COL_ORDER::CO_CURSOR);
	Scene()->COLMGR.Link((UINT)COL_ORDER::CO_CURSOR	, (UINT)COL_ORDER::CO_DROPITEM);
	Scene()->COLMGR.Link((UINT)COL_ORDER::CO_PLAYER_SUB	, (UINT)COL_ORDER::CO_DROPITEM);
	Scene()->COLMGR.Link((UINT)COL_ORDER::CO_DROPITEM, (UINT)COL_ORDER::CO_PLAYER_SUB);

	GameDirectory m_Dir;
	m_Dir.MoveParent(L"GameFramework");
	m_Dir.Move(L"Res");
	m_Dir.Move(L"Tex");
	
	GameTexture::Load(m_Dir.CreateGameFilePath(L"PlayerWalk.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"PlayerWalk.png"), 7, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"PlayerIdle.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"PlayerIdle.png"), 6, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"Pickaxe.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Pickaxe.png"), 1, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"Slime.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Slime.png"), 5, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"BoarIdle.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"BoarIdle.png"), 5, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"BoarWalk.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"BoarWalk.png"), 7, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"SkeletonIdle.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"SkeletonIdle.png"), 6, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"SkeletonWalk.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"SkeletonWalk.png"), 6, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"SkeletonUnburrow.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"SkeletonUnburrow.png"), 13, 1);

	m_Dir.MoveParent(L"GameFramework");
	m_Dir.Move(L"Res");
	m_Dir.Move(L"Tex");
	m_Dir.Move(L"Tile");

	GameTexture::Load(m_Dir.CreateGameFilePath(L"Tile1.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Tile1.png"), 7, 7);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"Tile1_2.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Tile1_2.png"), 7, 7);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"Tile2.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Tile2.png"), 7, 7);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"Tile2_2.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Tile2_2.png"), 7, 7);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"Tile3.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Tile3.png"), 7, 7);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"Tile3_2.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Tile3_2.png"), 7, 7);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"Tile4.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Tile4.png"), 7, 7);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"Tile4_2.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Tile4_2.png"), 7, 7);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"Tile5.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Tile5.png"), 7, 7);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"Tile5_2.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Tile5_2.png"), 7, 7);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"Tileset13.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Tileset13.png"), 11, 11);

	m_Dir.MoveParent(L"GameFramework");
	m_Dir.Move(L"Res");
	m_Dir.Move(L"Tex");

	GameTexture::Load(m_Dir.CreateGameFilePath(L"Tree.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Tree.png"), 4, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"Rock.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Rock.png"), 8, 1);

	Inventory::Load();
	Item::Load();
	MenuBar::Load();
	DropItem::Load();

	g_IsUIOn = false;

	{
		S_Ptr<GameActor> NewActor = CreateActor();
		NewActor->Trans()->LPOS({ 0.0f,0.0f,-10.0f });
		m_Cam = NewActor->AddCom<GameCamera>(10
			, (UINT)RENDER_ORDER::RO_LEVEL
			, (UINT)RENDER_ORDER::RO_PLAYER
			, (UINT)RENDER_ORDER::RO_MONSTER
			, (UINT)RENDER_ORDER::RO_MISC
			, (UINT)RENDER_ORDER::RO_ITEM
			, (UINT)RENDER_ORDER::RO_DROPITEM
			, (UINT)RENDER_ORDER::RO_UI);
		m_Cam->Size(LogicData::ScreenSize);
	}

	/*{
		S_Ptr<GameActor> NewActor = CreateActor();
		NewActor->Trans()->LPOS({ 0.0f,0.0f,-15.0f });
		m_UICam = NewActor->AddCom<GameCamera>(10
			, RENDER_ORDER::RO_UI);
		m_UICam->Size(LogicData::ScreenSize);
	}*/

	 
	{
		GameDirectory m_Dir;
		m_Dir.MoveParent(L"GameFramework");
		m_Dir.Move(L"Res");
		m_Dir.Move(L"Data");

		GameString Str = m_Dir.FullPath() + L"\\aaa.MapData";

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, Str, L"rb");
		
		S_Ptr<GameActor> NewActor = CreateActor();
		
		S_Ptr<RenderTileSub> NewTileSub = NewActor->AddCom<RenderTileSub>();
		NewTileSub->Load(pFile);
		
		S_Ptr<RenderTileBase> NewTileBase = NewActor->AddCom<RenderTileBase>();
		NewTileBase->Load(pFile);
		g_GroundTile = NewTileBase;
		
		S_Ptr<RenderTree> NewTree = NewActor->AddCom<RenderTree>();
		NewTree->Load(pFile, Scene());

		S_Ptr<RenderMisc> NewMisc = NewActor->AddCom<RenderMisc>();
		NewMisc->Load(pFile, Scene());
		
		//S_Ptr<RenderCW> NewCW = NewActor->AddCom<RenderCW>();
		//NewCW->Load(pFile, Scene());

		fclose(pFile); // ★
	}
	

	{
		m_InvenActor = CreateActor();
		S_Ptr<MenuBar> m_Inven = m_InvenActor->AddCom<MenuBar>();
		m_InvenActor->Trans()->LPOS({ -1000.0f, 0.0f, 0.0f });
	}

	{
		S_Ptr<GameActor> NewActor = CreateActor();
		NewActor->Trans()->LPOS({ -2.0f, -1.0f, 0.0f });
		NewActor->Trans()->LSCALE({ 1.0f, 1.0f, 1.0f });
		g_Hero = NewActor->AddCom<Hero>();
	}

	{
		S_Ptr<GameActor> NewActor = CreateActor();
		NewActor->Trans()->LPOS({ -2.0f, -2.0f, -1.0f });
		NewActor->Trans()->LSCALE({ 1.0f, 1.0f, 1.0f });
		S_Ptr<Slime> NewSlime = NewActor->AddCom<Slime>();
	}

	{
		S_Ptr<GameActor> NewActor = CreateActor();
		NewActor->Trans()->LPOS({ 3.0f, 3.0f, -1.0f });
		NewActor->Trans()->LSCALE({ 1.0f, 1.0f, 1.0f });
		S_Ptr<Slime> NewSlime = NewActor->AddCom<Slime>();
	}

	{
		S_Ptr<GameActor> NewActor = CreateActor();
		NewActor->Trans()->LPOS({ 0.0f, 6.0f, -1.0f });
		NewActor->Trans()->LSCALE({ 1.0f, 1.0f, 1.0f });
		S_Ptr<Boar> NewBoar = NewActor->AddCom<Boar>();
	}

	{
		S_Ptr<GameActor> NewActor = CreateActor();
		NewActor->Trans()->LPOS({ -1.0f, 6.0f, -1.0f });
		NewActor->Trans()->LSCALE({ 1.0f, 1.0f, 1.0f });
		S_Ptr<Skeleton> NewSkeleton = NewActor->AddCom<Skeleton>();
	}


	{
		/*for (int i = 0; i < 10; ++i)
		{
			S_Ptr<GameActor> NewActor = CreateActor();
			NewActor->Trans()->LSCALE({ 0.5f, 0.5f, 1.0f });
			NewActor->Trans()->LPOS({ -5.0f + i, 0.0f, 1.0f });
			S_Ptr<DropItem> NewItem = NewActor->AddCom<DropItem>();
			NewItem->SetDropItem(1);
		}*/
		
		/*for (int i = 0; i < 10; ++i)
		{
			S_Ptr<GameActor> NewActor = CreateActor();
			NewActor->Trans()->LSCALE({ 0.5f, 0.5f, 1.0f });
			NewActor->Trans()->LPOS({ -5.0f + i, 3.0f, 1.0f });
			S_Ptr<DropItem> NewItem = NewActor->AddCom<DropItem>();
			NewItem->SetDropItem(1);
		}*/

		/*for (int i = 0; i < 10; ++i)
		{
			S_Ptr<GameActor> NewActor = CreateActor();
			NewActor->Trans()->LSCALE({ 0.5f, 0.5f, 1.0f });
			NewActor->Trans()->LPOS({ -5.0f + i, 5.0f, 1.0f });
			S_Ptr<DropItem> NewItem = NewActor->AddCom<DropItem>();
			NewItem->SetDropItem(1);
		}*/
	}

	/*{
		S_Ptr<GameActor> NewActor = CreateActor();
		NewActor->Trans()->LSCALE({ 0.5f, 0.5f, 1.0f });
		NewActor->Trans()->LPOS({ 7.0f, 0.0f, 1.0f });
		S_Ptr<DropItem> NewItem = NewActor->AddCom<DropItem>();
		NewItem->SetDropItem(0);
	}*/

	{
		m_CursorActor = CreateActor();
		S_Ptr<GameCol> NewCol = m_CursorActor->AddCom<GameCol>(GameCol::COLTYPE::OBBRECT, (UINT)COL_ORDER::CO_CURSOR);
		m_CursorActor->Trans()->LSCALE({ 0.3f, 0.3f, 1.0f });
		S_Ptr<Cursor> NewCursor = m_CursorActor->AddCom<Cursor>();
	}

}

void PlayScene::Update()
{
	m_CursorActor->Trans()->LPOS({
		m_Cam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()).x,
		m_Cam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()).y, 
		0.0f
		});

	if (true == GameInput::Down(L"DEBUG_ON"))
	{
		if (GameCol::Debug == true)
		{
			GameCol::Debug = false;
		}
		else
		{
			GameCol::Debug = true;
		}
	}

	CVector m_Pos;
	m_Pos = g_Hero->Trans()->LPOS();
	m_Pos.z = -10;

	if (true == GameInput::Down(L"ESC"))
	{
		if (g_IsUIOn)
		{
			m_InvenActor->Trans()->LPOS({ -1000.0f, 0.0f, 0.0f });
			g_IsUIOn = false;
		}
		else
		{
			// 인벤토리를 열었을 때 플레이어는 움직이지 못하게 한다.
			m_InvenActor->Trans()->LPOS({ m_Pos.x, m_Pos.y, 0.0f });
			g_IsUIOn = true;
		}
	}

	m_Cam->Trans()->LPOS(m_Pos);

}

void PlayScene::DebugRender()
{
	wchar_t Arr[256];

	swprintf_s(Arr, L"ScreenToMousePos %f, %f"
		, m_Cam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()).x
		, m_Cam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()).y);
	GameFrameDebug::Draw2DFont(Arr, 20.0f, { 10, 10 }, { 1.0f, 1.0f, 1.0f, 1.0f });
	// GameFrameDebug::Draw2DFont(L"", 50.0f, { 0,0 }, { 1.0f,1.0f,1.0f,1.0f });

	swprintf_s(Arr, L"PlayerPos %f, %f, %d"
		, g_Hero->Trans()->WPOS().x
		, g_Hero->Trans()->WPOS().y
		, g_GroundTile->IsTile(g_Hero->Trans()->WPOS()));
	GameFrameDebug::Draw2DFont(Arr, 20.0f, { 10, 30 }, { 1.0f, 1.0f, 1.0f, 1.0f });

}