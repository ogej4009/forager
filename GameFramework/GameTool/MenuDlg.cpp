// MenuDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GameTool.h"
#include "afxdialogex.h"
#include "MenuDlg.h"

#include "MapSceneCom.h"
#include <GameDirectory.h>
#include <RenderTileBase.h>
#include <RenderTileSub.h>
#include <RenderTree.h>
#include <RenderMisc.h>
#include <RenderCW.h>

// MenuDlg 대화 상자

IMPLEMENT_DYNAMIC(MenuDlg, CDialogEx)

MenuDlg::MenuDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MenuDlg, pParent)

{

}

MenuDlg::~MenuDlg()
{
}

void MenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MENUDLGLIST, m_MenuDlgListCtrl);
}


BEGIN_MESSAGE_MAP(MenuDlg, CDialogEx)
	ON_LBN_SELCHANGE(IDC_MENUDLGLIST, &MenuDlg::OnLbnSelchangeRightdlglist)
	ON_BN_CLICKED(IDC_SAVEBUTTON, &MenuDlg::OnBnClickedSavebutton)
	ON_BN_CLICKED(IDC_LOADBUTTON, &MenuDlg::OnBnClickedLoadbutton)
	ON_BN_CLICKED(IDC_CLEARBUTTON, &MenuDlg::OnBnClickedClearbutton)
END_MESSAGE_MAP()


// MenuDlg 메시지 처리기



void MenuDlg::OnLbnSelchangeRightdlglist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	UpdateData(TRUE);
	
	int SIdx = m_MenuDlgListCtrl.GetCurSel();
	
	if (SIdx == 0)
	{
		CMapSceneCom::m_TileSetIdx = 0;
	}
	else if (SIdx == 1)
	{
		CMapSceneCom::m_TileSetIdx = 1;
	}
	else if (SIdx == 2)
	{
		CMapSceneCom::m_TileSetIdx = 2;
	}
	else if (SIdx == 3)
	{
		CMapSceneCom::m_TileSetIdx = 3;
	}
	else if (SIdx == 4)
	{
		CMapSceneCom::m_TileSetIdx = 4;
	}
	else if (SIdx == 5)
	{
		CMapSceneCom::m_TileSetIdx = 5;
	}
	else if (SIdx == 6)
	{
		CMapSceneCom::m_TileSetIdx = 6;
	}
	else if (SIdx == 7)
	{
		CMapSceneCom::m_TileSetIdx = 7;
	}
	else if (SIdx == 8)
	{
		CMapSceneCom::m_TileSetIdx = 8;
	}
	else if (SIdx == 9)
	{
		CMapSceneCom::m_TileSetIdx = 9;
	}
	else if (SIdx == 10)
	{
		CMapSceneCom::m_TileSetIdx = 10;
	}
	else if (SIdx == 11)
	{
		CMapSceneCom::m_TileSetIdx = 11;
	}
	else if (SIdx == 12)
	{
		CMapSceneCom::m_TileSetIdx = 12;
	}
	else if (SIdx == 13)
	{
		CMapSceneCom::m_TileSetIdx = 13;
	}
	else if (SIdx == 14)
	{
		CMapSceneCom::m_TileSetIdx = 14;
	}
	else if (SIdx == 15)
	{
		CMapSceneCom::m_TileSetIdx = 15;
	}
	else if (SIdx == 16)
	{
		CMapSceneCom::m_TileSetIdx = 16;
	}
	
	UpdateData(FALSE);
}


void MenuDlg::OnBnClickedSavebutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GameDirectory m_Dir;
	m_Dir.MoveParent(L"GameFramework");
	m_Dir.Move(L"Res");
	m_Dir.Move(L"Data");
	
	CString InitPath;
	CFileDialog dlgFileOpen(FALSE);
	OPENFILENAME& ofnOpen = dlgFileOpen.GetOFN();
	InitPath = m_Dir.FullPath().c_str();
	InitPath += L"\\";
	ofnOpen.lpstrInitialDir = InitPath.GetBuffer();
	
	CString SavePath;
	
	// 어떤 다이얼로그가 꺼질때까지 정지.
	if (IDOK == dlgFileOpen.DoModal())
	{
		SavePath = dlgFileOpen.GetFolderPath() + L"\\";
		SavePath += dlgFileOpen.GetFileName();
		if (-1 == SavePath.FindOneOf(L".MapData"))
		{
			SavePath += L".MapData";
		}
	}
	
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, SavePath.GetString(), L"wb");
	CMapSceneCom::R_TS->Save(pFile);
	CMapSceneCom::R_T->Save(pFile);
	CMapSceneCom::R_TREE->Save(pFile);
	CMapSceneCom::R_MISC->Save(pFile);
	//CMapSceneCom::WR->Save(pFile);
	
	fclose(pFile);
}


void MenuDlg::OnBnClickedLoadbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GameDirectory m_Dir;
	m_Dir.MoveParent(L"GameFramework");
	m_Dir.Move(L"Res");
	m_Dir.Move(L"Data");
	
	CString InitPath;
	CFileDialog dlgFileOpen(TRUE);
	OPENFILENAME& ofnOpen = dlgFileOpen.GetOFN();
	InitPath = m_Dir.FullPath().c_str();
	InitPath += L"\\";
	ofnOpen.lpstrInitialDir = InitPath.GetBuffer();
	
	CString SavePath;
	
	// 어떤 다이얼로그가 꺼질때까지 정지.
	if (IDOK == dlgFileOpen.DoModal())
	{
		SavePath = dlgFileOpen.GetFolderPath() + L"\\";
		SavePath += dlgFileOpen.GetFileName();
	}
	
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, SavePath.GetString(), L"rb");
	
	// Tile, TileB 저장
	RenderTree::g_IsLoad = true;
	RenderMisc::g_IsLoad = true;
	CMapSceneCom::R_TS->Load(pFile); // Tile
	CMapSceneCom::R_T->Load(pFile); // TileB
	CMapSceneCom::R_TREE->Load(pFile, GameScene::GetCurScene());// Tree
	CMapSceneCom::R_MISC->Load(pFile, GameScene::GetCurScene()); // Obj
	//CMapSceneCom::WR->Load(pFile, CGameScene::GetCurScene());
	
	fclose(pFile);
	
}


void MenuDlg::OnBnClickedClearbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMapSceneCom::R_TS->Clear();
	CMapSceneCom::R_T->Clear();
	CMapSceneCom::R_TREE->Clear();
	CMapSceneCom::R_MISC->Clear();
	//CMapSceneCom::WR->Clear();
}


BOOL MenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	RenderTree::g_IsLoad = false;
	RenderMisc::g_IsLoad = false;

	//mapObjList.InsertString(0, L"Water");
	m_MenuDlgListCtrl.InsertString(0, L"Tile1");
	m_MenuDlgListCtrl.InsertString(1, L"Tile2");
	m_MenuDlgListCtrl.InsertString(2, L"Tile3");
	m_MenuDlgListCtrl.InsertString(3, L"Tile4");
	m_MenuDlgListCtrl.InsertString(4, L"Tile5");
	m_MenuDlgListCtrl.InsertString(5, L"Tree1");
	m_MenuDlgListCtrl.InsertString(6, L"Tree2");
	m_MenuDlgListCtrl.InsertString(7, L"Tree3");
	m_MenuDlgListCtrl.InsertString(8, L"Tree4");
	m_MenuDlgListCtrl.InsertString(9, L"Rock1_1");
	m_MenuDlgListCtrl.InsertString(10, L"Rock1_2");
	m_MenuDlgListCtrl.InsertString(11, L"Rock2_1");
	m_MenuDlgListCtrl.InsertString(12, L"Rock2_2");
	m_MenuDlgListCtrl.InsertString(13, L"Rock3_1");
	m_MenuDlgListCtrl.InsertString(14, L"Rock3_2");
	m_MenuDlgListCtrl.InsertString(15, L"Rock4_1");
	m_MenuDlgListCtrl.InsertString(16, L"Rock4_2");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
