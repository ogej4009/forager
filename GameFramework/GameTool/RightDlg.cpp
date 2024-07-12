// RightDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GameTool.h"
#include "afxdialogex.h"
#include "RightDlg.h"

#include "ToolProgress.h"
#include <GameScene.h>
#include "MenuDlg.h"

// RightDlg 대화 상자

IMPLEMENT_DYNAMIC(RightDlg, CDialogEx)

RightDlg::RightDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RightDlg, pParent)
{

}

RightDlg::~RightDlg()
{
	for (size_t i = 0; i < ArrDlg.size(); i++)
	{
		delete ArrDlg[i];
	}
}

void RightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TOOLMENUTAB, m_ToolMenuTab);
}


BEGIN_MESSAGE_MAP(RightDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TOOLMENUTAB, &RightDlg::OnTcnSelchangeToolmenutab)
END_MESSAGE_MAP()


// RightDlg 메시지 처리기

#define MINTAP 0
int TabCount = 0;
#define PLUSTAP TabCount++
#define MAXTAP TabCount


BOOL RightDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_ToolMenuTab.InsertItem(PLUSTAP, L"MAP");
	//TabMenu.InsertItem(PLUSTAP, L"OBJECT");

	ToolProgress::Init();

	TCreateDlg<MenuDlg>(IDD_MenuDlg);

	ArrDlg[0]->ShowWindow(SW_SHOW);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void RightDlg::OnTcnSelchangeToolmenutab(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	UpdateData(TRUE);
		
	int SIdx = m_ToolMenuTab.GetCurSel();
	
	WCHAR ArrText[256];
	TCITEMW Item;
	Item.mask = TCIF_TEXT;
	Item.cchTextMax = 256;
	Item.pszText = ArrText;
	m_ToolMenuTab.GetItem(SIdx, &Item);
	
	if (MINTAP > SIdx || MAXTAP < SIdx)
	{
		return;
	}
	
	for (size_t i = 0; i < ArrDlg.size(); i++)
	{
		ArrDlg[i]->ShowWindow(SW_HIDE);
	}
	
	ArrDlg[SIdx]->ShowWindow(SW_SHOW);
	
	GameScene::ChangeScene(ArrText);

	UpdateData(FALSE);

}


BOOL RightDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//	if (pMsg->message == WM_KEYDOWN)
	//	{
	//		if (pMsg->wParam == VK_RETURN) // ENTER키 눌릴 시
	//			return TRUE;
	//		else if (pMsg->wParam == VK_ESCAPE) // ESC키 눌릴 시
	//			return TRUE;
	//	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
