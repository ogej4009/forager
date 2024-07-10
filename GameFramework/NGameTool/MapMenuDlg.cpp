// MapMenuDlb.cpp: 구현 파일
//

#include "pch.h"
#include "NGameTool.h"
#include "MapMenuDlg.h"
#include "afxdialogex.h"
#include "MapSceneCom.h"
#include <GameDir.h>
#include <TileRender.h>
#include <TileBRender.h>
#include <TreeRender.h>
#include <ObjRender.h>
#include <WRender.h>



// CMapMenuDlb 대화 상자

IMPLEMENT_DYNAMIC(CMapMenuDlg, CDialogEx)

CMapMenuDlg::CMapMenuDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAPMENUDLG, pParent)
{

}

CMapMenuDlg::~CMapMenuDlg()
{
}

void CMapMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAPOBJLIST, mapObjList);
}


BEGIN_MESSAGE_MAP(CMapMenuDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SAVEBTN, &CMapMenuDlg::OnBnClickedSavebtn)
	ON_BN_CLICKED(IDC_LOADBTN, &CMapMenuDlg::OnBnClickedLoadbtn)
	ON_BN_CLICKED(IDC_CLEARBTN, &CMapMenuDlg::OnBnClickedClearbtn)
	ON_LBN_SELCHANGE(IDC_MAPOBJLIST, &CMapMenuDlg::OnLbnSelchangeMapobjlist)
END_MESSAGE_MAP()


// CMapMenuDlb 메시지 처리기


void CMapMenuDlg::OnBnClickedSavebtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CGameDir m_Dir;
	m_Dir.MoveParent(L"NDX11");
	m_Dir.Move(L"BIN");
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
	CMapSceneCom::TBR->Save(pFile);
	CMapSceneCom::TR->Save(pFile);
	CMapSceneCom::TOR->Save(pFile);
	CMapSceneCom::OR->Save(pFile);
	//CMapSceneCom::WR->Save(pFile);

	fclose(pFile);
}


void CMapMenuDlg::OnBnClickedLoadbtn()
{
	CGameDir m_Dir;
	m_Dir.MoveParent(L"NDX11");
	m_Dir.Move(L"BIN");
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
	CTreeRender::IsLoad = true;
	CObjRender::IsLoad = true;
	CMapSceneCom::TBR->Load(pFile); // Tile
	CMapSceneCom::TR->Load(pFile); // TileB
	CMapSceneCom::TOR->Load(pFile, CGameScene::GetCurScene());// Tree
	CMapSceneCom::OR->Load(pFile, CGameScene::GetCurScene()); // Obj
	//CMapSceneCom::WR->Load(pFile, CGameScene::GetCurScene());

	fclose(pFile);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMapMenuDlg::OnBnClickedClearbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMapSceneCom::TBR->Clear();
	CMapSceneCom::TR->Clear();
	CMapSceneCom::TOR->Clear();
	CMapSceneCom::OR->Clear();
	//CMapSceneCom::WR->Clear();
}


BOOL CMapMenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	CTreeRender::IsLoad = false;
	CObjRender::IsLoad = false;

	//mapObjList.InsertString(0, L"Water");
	mapObjList.InsertString(0, L"Tile1");
	mapObjList.InsertString(1, L"Tile2");
	mapObjList.InsertString(2, L"Tile3");
	mapObjList.InsertString(3, L"Tile4");
	mapObjList.InsertString(4, L"Tile5");
	mapObjList.InsertString(5, L"Tree1");
	mapObjList.InsertString(6, L"Tree2");
	mapObjList.InsertString(7, L"Tree3");
	mapObjList.InsertString(8, L"Tree4");
	mapObjList.InsertString(9, L"Rock1_1");
	mapObjList.InsertString(10, L"Rock1_2");
	mapObjList.InsertString(11, L"Rock2_1");
	mapObjList.InsertString(12, L"Rock2_2");
	mapObjList.InsertString(13, L"Rock3_1");
	mapObjList.InsertString(14, L"Rock3_2");
	mapObjList.InsertString(15, L"Rock4_1");
	mapObjList.InsertString(16, L"Rock4_2");



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMapMenuDlg::OnLbnSelchangeMapobjlist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	UpdateData(TRUE);

	int SIdx = mapObjList.GetCurSel();

	/*if (SIdx == 0)
	{
		CMapSceneCom::m_TileSetIdx = 0;
	}*/
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


