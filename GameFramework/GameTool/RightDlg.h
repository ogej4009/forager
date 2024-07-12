#pragma once
#include "afxdialogex.h"

#include <vector>
#include <GameMath.h>

// RightDlg 대화 상자

class RightDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RightDlg)

public:
	RightDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~RightDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RightDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

public:
	std::vector<CDialogEx*> ArrDlg;

public:
	template<typename T>
	void TCreateDlg(unsigned int _ID)
	{
		T* NewDlg = new T();
		NewDlg->Create(_ID, &TabMenu);
		NewDlg->ShowWindow(SW_HIDE);
		NewDlg->SetBackgroundColor(RGB(200, 200, 200));
		NewDlg->SetWindowPos(nullptr, 4, 20, 500, 500, 0);
		ArrDlg.push_back(NewDlg);
	}

	CTabCtrl m_ToolMenuTab;
	afx_msg void OnTcnSelchangeToolmenutab(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
};
