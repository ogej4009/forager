// RightDlg.cpp: 구현 파일
//

#include "pch.h"
#include "NGameTool.h"
#include "RightDlg.h"
#include "afxdialogex.h"
#include "ToolProgress.h"
#include <GameScene.h>
#include "MapMenuDlg.h"


// CRightDlg 대화 상자

IMPLEMENT_DYNAMIC(CRightDlg, CDialogEx)

CRightDlg::CRightDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RIGHTVIEWDLG, pParent)
{

}

CRightDlg::~CRightDlg()
{
	for (size_t i = 0; i < ArrDlg.size(); i++)
	{
		delete ArrDlg[i];
	}
}

void CRightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TOOLMENU, TabMenu);
}


BEGIN_MESSAGE_MAP(CRightDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TOOLMENU, &CRightDlg::OnTcnSelchangeToolmenu)
END_MESSAGE_MAP()


// CRightDlg 메시지 처리기


#define MINTAP 0
int TabCount = 0;
#define PLUSTAP TabCount++
#define MAXTAP TabCount


BOOL CRightDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	TabMenu.InsertItem(PLUSTAP, L"MAP");
	//TabMenu.InsertItem(PLUSTAP, L"OBJECT");

	CToolProgress::Init();

	NCreateDlg<CMapMenuDlg>(IDD_MAPMENUDLG);

	ArrDlg[0]->ShowWindow(SW_SHOW);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CRightDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN) // ENTER키 눌릴 시
			return TRUE;
		else if (pMsg->wParam == VK_ESCAPE) // ESC키 눌릴 시
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CRightDlg::OnTcnSelchangeToolmenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	UpdateData(TRUE);

	
	int SIdx = TabMenu.GetCurSel();

	WCHAR ArrText[256];
	TCITEMW Item;
	Item.mask = TCIF_TEXT;
	Item.cchTextMax = 256;
	Item.pszText = ArrText;
	TabMenu.GetItem(SIdx, &Item);


	if (MINTAP > SIdx || MAXTAP < SIdx)
	{
		return;
	}

	for (size_t i = 0; i < ArrDlg.size(); i++)
	{
		ArrDlg[i]->ShowWindow(SW_HIDE);
	}

	ArrDlg[SIdx]->ShowWindow(SW_SHOW);


	CGameScene::ChangeScene(ArrText);

	UpdateData(FALSE);
}
