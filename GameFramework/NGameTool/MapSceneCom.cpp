#include "pch.h"
#include "MapSceneCom.h"
#include <LogicHeader.h>
#include <GameInput.h>
#include <GameActor.h>
#include <Trans.h>
#include <Col.h>
#include <Render.h>
#include <Cam.h>
#include <GameDir.h>
#include <ImgRender.h>
#include <Tex.h>
#include <2DSprite.h>
#include <3DDebug.h>
#include <TileRender.h>
#include <TileBRender.h>
#include <TreeRender.h>
#include <ObjRender.h>
#include <WRender.h>


CPTR<CTileRender> CMapSceneCom::TR;
CPTR<CTileBRender> CMapSceneCom::TBR;

CPTR<CTreeRender> CMapSceneCom::TOR;
CPTR<CObjRender> CMapSceneCom::OR;
CPTR<CWRender> CMapSceneCom::WR;
int CMapSceneCom::m_TileSetIdx;



CMapSceneCom::CMapSceneCom()
{
}

CMapSceneCom::~CMapSceneCom()
{
}



void CMapSceneCom::Loading()
{
	CGameInput::CreateKey(L"MML", 'A');
	CGameInput::CreateKey(L"MMR", 'D');
	CGameInput::CreateKey(L"MMU", 'W');
	CGameInput::CreateKey(L"MMD", 'S');
	CGameInput::CreateKey(L"TILECREATE", VK_LBUTTON);


	CGameDir m_Dir;
	m_Dir.MoveParent(L"NDX11");
	m_Dir.Move(L"BIN");
	m_Dir.Move(L"Tex");
	m_Dir.Move(L"Tile");

	
	// 타일 이미지 로드
	CTex::Load(m_Dir.CreateGameFilePath(L"Tile1.png"));
	C2DSprite::Create(m_Dir.CreateGameFilePath(L"Tile1.png"), 7, 7);
	CTex::Load(m_Dir.CreateGameFilePath(L"Tile1_2.png"));
	C2DSprite::Create(m_Dir.CreateGameFilePath(L"Tile1_2.png"), 7, 7);
	CTex::Load(m_Dir.CreateGameFilePath(L"Tile2.png"));
	C2DSprite::Create(m_Dir.CreateGameFilePath(L"Tile2.png"), 7, 7);
	CTex::Load(m_Dir.CreateGameFilePath(L"Tile2_2.png"));
	C2DSprite::Create(m_Dir.CreateGameFilePath(L"Tile2_2.png"), 7, 7);
	CTex::Load(m_Dir.CreateGameFilePath(L"Tile3.png"));
	C2DSprite::Create(m_Dir.CreateGameFilePath(L"Tile3.png"), 7, 7);
	CTex::Load(m_Dir.CreateGameFilePath(L"Tile3_2.png"));
	C2DSprite::Create(m_Dir.CreateGameFilePath(L"Tile3_2.png"), 7, 7);
	CTex::Load(m_Dir.CreateGameFilePath(L"Tile4.png"));
	C2DSprite::Create(m_Dir.CreateGameFilePath(L"Tile4.png"), 7, 7);
	CTex::Load(m_Dir.CreateGameFilePath(L"Tile4_2.png"));
	C2DSprite::Create(m_Dir.CreateGameFilePath(L"Tile4_2.png"), 7, 7);
	CTex::Load(m_Dir.CreateGameFilePath(L"Tile5.png"));
	C2DSprite::Create(m_Dir.CreateGameFilePath(L"Tile5.png"), 7, 7);
	CTex::Load(m_Dir.CreateGameFilePath(L"Tile5_2.png"));
	C2DSprite::Create(m_Dir.CreateGameFilePath(L"Tile5_2.png"), 7, 7);
	CTex::Load(m_Dir.CreateGameFilePath(L"Tileset13.png"));
	C2DSprite::Create(m_Dir.CreateGameFilePath(L"Tileset13.png"), 11, 11);

	

	// 오브젝트 이미지 로드
	m_Dir.MoveParent(L"NDX11");
	m_Dir.Move(L"BIN");
	m_Dir.Move(L"Tex");
	CTex::Load(m_Dir.CreateGameFilePath(L"Tree.png"));
	C2DSprite::Create(m_Dir.CreateGameFilePath(L"Tree.png"), 4, 1);
	CTex::Load(m_Dir.CreateGameFilePath(L"Rock.png"));
	C2DSprite::Create(m_Dir.CreateGameFilePath(L"Rock.png"), 8, 1);

	//CMapTreeCreate::Loading();

	{
		CPTR<CGameActor> PTR = CreateActor(L"MainCam");
		PTR->Trans()->WPOS({ 0.0f,0.0f,-10.0f });
		MapCam = PTR->AddCom<CCam>(10, RG_MAP, RG_PLAYER, RG_MONSTER);
		MapCam->Size(LOGICVAR::Screensize);
	}

	


	{
		// TileB
		CPTR<CGameActor> PTR = CreateActor();
		PTR->Trans()->WPOS({ 0.0f, 0.0f, 0.0f });
		PTR->Trans()->WSCALE({ 1.0f, 1.0f, 1.0f });
		TBR = PTR->AddCom<CTileBRender>();
		TBR->Sprite(L"Tile1_2.png");
	}

	

	//{
	//	// W
	//	CPTR<CGameActor> PTR = CreateActor();
	//	PTR->Trans()->LPOS({ 0.0f, 0.0f, 0.0f });
	//	PTR->Trans()->LSCALE({ 1.0f, 1.0f, 1.0f });
	//	WR = PTR->AddCom<CWRender>();
	//	WR->Sprite(L"Tileset13.png");
	//	WR->Trans()->LSCALE({ 1.0f, 1.0f, 1.0f });

	//}

	

	{
		// Tile
		CPTR<CGameActor> PTR = CreateActor();
		PTR->Trans()->WPOS({ 0.0f, 0.0f, 0.0f });
		PTR->Trans()->WSCALE({ 1.0f, 1.0f, 1.0f });
		TR = PTR->AddCom<CTileRender>();
		TR->Sprite(L"Tile1.png");
		
	}

	

	{
		// Tree
		CPTR<CGameActor> PTR = CreateActor();
		PTR->Trans()->LPOS({ 0.0f, 0.0f, 0.0f });
		PTR->Trans()->LSCALE({ 1.0f, 1.0f, 1.0f });
		TOR = PTR->AddCom<CTreeRender>();
		TOR->Sprite(L"Tree.png");
		TOR->Trans()->LSCALE({ 2.0f, 2.0f, 1.0f });
		

	}

	{
		// Rock
		CPTR<CGameActor> PTR = CreateActor();
		PTR->Trans()->LPOS({ 0.0f, 0.0f, 0.0f });
		PTR->Trans()->LSCALE({ 1.0f, 1.0f, 1.0f });
		OR = PTR->AddCom<CObjRender>();
		OR->Sprite(L"Rock.png");
		OR->Trans()->LSCALE({ 1.0f, 1.0f, 1.0f });

	}

	
	

}

void CMapSceneCom::Update()
{
	if (true == CGameInput::Press(L"MML"))
	{
		MapCam->Trans()->LMOVETOTIMESPEED(CVEC4::LEFT, 2.0f);
	}
	if (true == CGameInput::Press(L"MMR"))
	{
		MapCam->Trans()->LMOVETOTIMESPEED(CVEC4::RIGHT, 2.0f);
	}
	if (true == CGameInput::Press(L"MMU"))
	{
		MapCam->Trans()->LMOVETOTIMESPEED(CVEC4::UP, 2.0f);
	}
	if (true == CGameInput::Press(L"MMD"))
	{
		MapCam->Trans()->LMOVETOTIMESPEED(CVEC4::DOWN, 2.0f);
	}


	// 왼쪽마우스 임시로 타일 배치, 타일봇 배치할 예정
	// RightView에서 배치할 오브젝트 선택 후 배치하도록 
	if (true == CGameInput::Press(L"TILECREATE"))
	{
		if (MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()).x < 8+ MapCam->Trans()->WPOS().x &&
			MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()).x > -8 + MapCam->Trans()->WPOS().x &&
			MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()).y < 4 + MapCam->Trans()->WPOS().y &&
			MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()).y > -4 + MapCam->Trans()->WPOS().y)
		{
			CraeteTileSet(m_TileSetIdx);
		}
		
	}

	// 오른쪽 마우스 임시로 나무 배치할 예정


}



void CMapSceneCom::DebugRender()
{
	wchar_t Arr[256];
	swprintf_s(Arr, L"MousePos %f, %f", CGameWin::MainWindow()->MousePos().x, CGameWin::MainWindow()->MousePos().y);
	C3DDebug::Draw2DFont(Arr, 20.0f, { 100, 80 }, { 1.0f, 1.0f, 1.0f, 1.0f });

	swprintf_s(Arr, L"MousePos3D %f, %f", CGameWin::MainWindow()->MousePos3D().x, CGameWin::MainWindow()->MousePos3D().y);
	C3DDebug::Draw2DFont(Arr, 20.0f, { 100, 100 }, { 1.0f, 1.0f, 1.0f, 1.0f });

	swprintf_s(Arr, L"CamPos %f, %f", MapCam->Trans()->WPOS().x, MapCam->Trans()->WPOS().y);
	C3DDebug::Draw2DFont(Arr, 20.0f, { 100, 120 }, { 1.0f, 1.0f, 1.0f, 1.0f });

	swprintf_s(Arr, L"CamScreenSize %f, %f"
		, MapCam->Size().x
		, MapCam->Size().y);
	C3DDebug::Draw2DFont(Arr, 20.0f, { 100, 140 }, { 1.0f, 1.0f, 1.0f, 1.0f });

	swprintf_s(Arr, L"ScreenToMousePos %f, %f"
		, MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()).x
		, MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()).y);
	C3DDebug::Draw2DFont(Arr, 20.0f, { 100, 160 }, { 1.0f, 1.0f, 1.0f, 1.0f });



}

void CMapSceneCom::CraeteTileSet(unsigned int _Idx)
{
	//if (_Idx == 0)
	//{
	//	// Water
	//	WR->Sprite(L"Tileset13.png");
	//	WR->CreateObj(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()), 97);
	//}
	if (_Idx == 0)
	{
		// Tile1
		TBR->Sprite(L"Tile1_2.png");
		TR->Sprite(L"Tile1.png");
		TBR->CreateTileB(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()));
		TR->CreateTile(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()));
	}
	else if (_Idx == 1)
	{
		// Tile2
		TBR->Sprite(L"Tile2_2.png");
		TR->Sprite(L"Tile2.png");
		TBR->CreateTileB(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()));
		TR->CreateTile(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()));
	}
	else if (_Idx == 2)
	{
		// Tile2
		TBR->Sprite(L"Tile3_2.png");
		TR->Sprite(L"Tile3.png");
		TBR->CreateTileB(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()));
		TR->CreateTile(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()));
	}
	else if (_Idx == 3)
	{
		// Tile2
		TBR->Sprite(L"Tile4_2.png");
		TR->Sprite(L"Tile4.png");
		TBR->CreateTileB(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()));
		TR->CreateTile(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()));
	}
	else if (_Idx == 4)
	{
		// Tile2
		TBR->Sprite(L"Tile5_2.png");
		TR->Sprite(L"Tile5.png");
		TBR->CreateTileB(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()));
		TR->CreateTile(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()));
	}
	else if (_Idx == 5)
	{
		TOR->Sprite(L"Tree.png");
		TOR->CreateTileObj(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()), 0);
	}
	else if (_Idx == 6)
	{
		TOR->Sprite(L"Tree.png");
		TOR->CreateTileObj(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()), 1);	
	}
	else if (_Idx == 7)
	{
		TOR->Sprite(L"Tree.png");
		TOR->CreateTileObj(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()), 2);
	}
	else if (_Idx == 8)
	{
		TOR->Sprite(L"Tree.png");
		TOR->CreateTileObj(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()), 3);
	}
	else if (_Idx == 9)
	{
		OR->Sprite(L"Rock.png");
		OR->CreateObj(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()), 0);
	}
	else if (_Idx == 10)
	{
		OR->Sprite(L"Rock.png");
		OR->CreateObj(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()), 1);
	}
	else if (_Idx == 11)
	{
		OR->Sprite(L"Rock.png");
		OR->CreateObj(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()), 2);
	}
	else if (_Idx == 12)
	{
		OR->Sprite(L"Rock.png");
		OR->CreateObj(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()), 3);
	}
	else if (_Idx == 13)
	{
		OR->Sprite(L"Rock.png");
		OR->CreateObj(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()), 4);
	}
	else if (_Idx == 14)
	{
		OR->Sprite(L"Rock.png");
		OR->CreateObj(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()), 5);
	}
	else if (_Idx == 15)
	{
		OR->Sprite(L"Rock.png");
		OR->CreateObj(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()), 6);
	}
	else if (_Idx == 16)
	{
		OR->Sprite(L"Rock.png");
		OR->CreateObj(MapCam->ScreenPos3DToWorldPos(CGameWin::MainWindow()->MousePos3D()), 7);
	}
}

