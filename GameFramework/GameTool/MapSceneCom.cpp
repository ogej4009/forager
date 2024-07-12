#include "pch.h"
#include "MapSceneCom.h"

#include <LogicData.h>
#include <GameInput.h>
#include <GameActor.h>
#include <GameTransform.h>
#include <GameCol.h>
#include <GameRender.h>
#include <GameCamera.h>
#include <GameDirectory.h>
#include <GameSprite.h>
#include <GameTexture.h>
#include <GameSprite.h>
#include <GameFrameDebug.h>
#include <RenderTileBase.h>
#include <RenderTileSub.h>
#include <RenderTree.h>
#include <RenderMisc.h>
#include <RenderCW.h>


S_Ptr<RenderTileBase>	CMapSceneCom::R_T;
S_Ptr<RenderTileSub>	CMapSceneCom::R_TS;
S_Ptr<RenderTree>		CMapSceneCom::R_TREE;
S_Ptr<RenderMisc>		CMapSceneCom::R_MISC;
S_Ptr<RenderCW>			CMapSceneCom::R_CW;
int CMapSceneCom::m_TileSetIdx;



CMapSceneCom::CMapSceneCom()
{
}

CMapSceneCom::~CMapSceneCom()
{
}



void CMapSceneCom::Loading()
{
	GameInput::CreateKey(L"MML", 'A');
	GameInput::CreateKey(L"MMR", 'D');
	GameInput::CreateKey(L"MMU", 'W');
	GameInput::CreateKey(L"MMD", 'S');
	GameInput::CreateKey(L"TILECREATE", VK_LBUTTON);


	GameDirectory m_Dir;
	m_Dir.MoveParent(L"GameFramework");
	m_Dir.Move(L"Res");
	m_Dir.Move(L"Tex");
	m_Dir.Move(L"Tile");


	// 타일 이미지 로드
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



	// 오브젝트 이미지 로드
	m_Dir.MoveParent(L"GameFramework");
	m_Dir.Move(L"Res");
	m_Dir.Move(L"Tex");
	GameTexture::Load(m_Dir.CreateGameFilePath(L"Tree.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Tree.png"), 4, 1);
	GameTexture::Load(m_Dir.CreateGameFilePath(L"Rock.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"Rock.png"), 8, 1);

	//CMapTreeCreate::Loading();

	{
		S_Ptr<GameActor> PTR = CreateActor();
		PTR->Trans()->WPOS({ 0.0f,0.0f,-10.0f });
		MapCam = PTR->AddCom<GameCamera>(10, RENDER_ORDER::RO_LEVEL
			, RENDER_ORDER::RO_PLAYER
			, RENDER_ORDER::RO_MONSTER);
		MapCam->Size(LogicData::ScreenSize);
	}




	{
		// TileB
		S_Ptr<GameActor> PTR = CreateActor();
		PTR->Trans()->WPOS({ 0.0f, 0.0f, 0.0f });
		PTR->Trans()->WSCALE({ 1.0f, 1.0f, 1.0f });
		R_TS = PTR->AddCom<RenderTileSub>();
		R_TS->Sprite(L"Tile1_2.png");
	}

	{
		// Tile
		S_Ptr<GameActor> PTR = CreateActor();
		PTR->Trans()->WPOS({ 0.0f, 0.0f, 0.0f });
		PTR->Trans()->WSCALE({ 1.0f, 1.0f, 1.0f });
		R_T = PTR->AddCom<RenderTileBase>();
		R_T->Sprite(L"Tile1.png");

	}

	{
		// Tree
		S_Ptr<GameActor> PTR = CreateActor();
		PTR->Trans()->LPOS({ 0.0f, 0.0f, 0.0f });
		PTR->Trans()->LSCALE({ 1.0f, 1.0f, 1.0f });
		R_TREE = PTR->AddCom<RenderTree>();
		R_TREE->Sprite(L"Tree.png");
		R_TREE->Trans()->LSCALE({ 2.0f, 2.0f, 1.0f });


	}

	{
		// Rock
		S_Ptr<GameActor> PTR = CreateActor();
		PTR->Trans()->LPOS({ 0.0f, 0.0f, 0.0f });
		PTR->Trans()->LSCALE({ 1.0f, 1.0f, 1.0f });
		R_MISC = PTR->AddCom<RenderMisc>();
		R_MISC->Sprite(L"Rock.png");
		R_MISC->Trans()->LSCALE({ 1.0f, 1.0f, 1.0f });

	}

}

void CMapSceneCom::Update()
{
	if (true == GameInput::Press(L"MML"))
	{
		MapCam->Trans()->LMOVETOTIMESPEED(CVector::LEFT, 2.0f);
	}
	if (true == GameInput::Press(L"MMR"))
	{
		MapCam->Trans()->LMOVETOTIMESPEED(CVector::RIGHT, 2.0f);
	}
	if (true == GameInput::Press(L"MMU"))
	{
		MapCam->Trans()->LMOVETOTIMESPEED(CVector::UP, 2.0f);
	}
	if (true == GameInput::Press(L"MMD"))
	{
		MapCam->Trans()->LMOVETOTIMESPEED(CVector::DOWN, 2.0f);
	}


	// 왼쪽마우스 임시로 타일 배치, 타일봇 배치할 예정
	// RightView에서 배치할 오브젝트 선택 후 배치하도록 
	if (true == GameInput::Press(L"TILECREATE"))
	{
		if (MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()).x < 8 + MapCam->Trans()->WPOS().x &&
			MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()).x > -8 + MapCam->Trans()->WPOS().x &&
			MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()).y < 4 + MapCam->Trans()->WPOS().y &&
			MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()).y > -4 + MapCam->Trans()->WPOS().y)
		{
			CraeteTileSet(m_TileSetIdx);
		}

	}

	// 오른쪽 마우스 임시로 나무 배치할 예정


}



void CMapSceneCom::DebugRender()
{
	wchar_t Arr[256];
	swprintf_s(Arr, L"MousePos %f, %f", GameWin::MainWindow()->MousePos().x, GameWin::MainWindow()->MousePos().y);
	GameFrameDebug::Draw2DFont(Arr, 20.0f, { 100, 80 }, { 1.0f, 1.0f, 1.0f, 1.0f });

	swprintf_s(Arr, L"MousePos3D %f, %f", GameWin::MainWindow()->MousePos3D().x, GameWin::MainWindow()->MousePos3D().y);
	GameFrameDebug::Draw2DFont(Arr, 20.0f, { 100, 100 }, { 1.0f, 1.0f, 1.0f, 1.0f });

	swprintf_s(Arr, L"CamPos %f, %f", MapCam->Trans()->WPOS().x, MapCam->Trans()->WPOS().y);
	GameFrameDebug::Draw2DFont(Arr, 20.0f, { 100, 120 }, { 1.0f, 1.0f, 1.0f, 1.0f });

	swprintf_s(Arr, L"CamScreenSize %f, %f"
		, MapCam->Size().x
		, MapCam->Size().y);
	GameFrameDebug::Draw2DFont(Arr, 20.0f, { 100, 140 }, { 1.0f, 1.0f, 1.0f, 1.0f });

	swprintf_s(Arr, L"ScreenToMousePos %f, %f"
		, MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()).x
		, MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()).y);
	GameFrameDebug::Draw2DFont(Arr, 20.0f, { 100, 160 }, { 1.0f, 1.0f, 1.0f, 1.0f });



}

void CMapSceneCom::CraeteTileSet(unsigned int _Idx)
{
	
/*
	R_T;
	R_TS;
	R_TREE;
	R_MISC;
	R_CW;
*/

	if (_Idx == 0)
	{
		// Tile1
		R_TS->Sprite(L"Tile1_2.png");
		R_T->Sprite(L"Tile1.png");
		R_TS->CreateTileB(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()));
		R_T->CreateTile(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()));
	}
	else if (_Idx == 1)
	{
		// Tile2
		R_TS->Sprite(L"Tile2_2.png");
		R_T->Sprite(L"Tile2.png");
		R_TS->CreateTileB(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()));
		R_T->CreateTile(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()));
	}
	else if (_Idx == 2)
	{
		// Tile2
		R_TS->Sprite(L"Tile3_2.png");
		R_T->Sprite(L"Tile3.png");
		R_TS->CreateTileB(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()));
		R_T->CreateTile(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()));
	}
	else if (_Idx == 3)
	{
		// Tile2
		R_TS->Sprite(L"Tile4_2.png");
		R_T->Sprite(L"Tile4.png");
		R_TS->CreateTileB(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()));
		R_T->CreateTile(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()));
	}
	else if (_Idx == 4)
	{
		// Tile2
		R_TS->Sprite(L"Tile5_2.png");
		R_T->Sprite(L"Tile5.png");
		R_TS->CreateTileB(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()));
		R_T->CreateTile(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()));
	}
	else if (_Idx == 5)
	{
		R_TREE->Sprite(L"Tree.png");
		R_TREE->CreateTileObj(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()), 0);
	}
	else if (_Idx == 6)
	{
		R_TREE->Sprite(L"Tree.png");
		R_TREE->CreateTileObj(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()), 1);
	}
	else if (_Idx == 7)
	{
		R_TREE->Sprite(L"Tree.png");
		R_TREE->CreateTileObj(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()), 2);
	}
	else if (_Idx == 8)
	{
		R_TREE->Sprite(L"Tree.png");
		R_TREE->CreateTileObj(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()), 3);
	}
	else if (_Idx == 9)
	{
		R_MISC->Sprite(L"Rock.png");
		R_MISC->CreateObj(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()), 0);
	}
	else if (_Idx == 10)
	{
		R_MISC->Sprite(L"Rock.png");
		R_MISC->CreateObj(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()), 1);
	}
	else if (_Idx == 11)
	{
		R_MISC->Sprite(L"Rock.png");
		R_MISC->CreateObj(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()), 2);
	}
	else if (_Idx == 12)
	{
		R_MISC->Sprite(L"Rock.png");
		R_MISC->CreateObj(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()), 3);
	}
	else if (_Idx == 13)
	{
		R_MISC->Sprite(L"Rock.png");
		R_MISC->CreateObj(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()), 4);
	}
	else if (_Idx == 14)
	{
		R_MISC->Sprite(L"Rock.png");
		R_MISC->CreateObj(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()), 5);
	}
	else if (_Idx == 15)
	{
		R_MISC->Sprite(L"Rock.png");
		R_MISC->CreateObj(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()), 6);
	}
	else if (_Idx == 16)
	{
		R_MISC->Sprite(L"Rock.png");
		R_MISC->CreateObj(MapCam->ScreenPos3DToWorldPos(GameWin::MainWindow()->MousePos3D()), 7);
	}
}

