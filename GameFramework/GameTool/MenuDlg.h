#pragma once
#include "afxdialogex.h"


// MenuDlg 대화 상자

class MenuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MenuDlg)

public:
	MenuDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MenuDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MenuDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLbnSelchangeRightdlglist();
	afx_msg void OnBnClickedSavebutton();
	afx_msg void OnBnClickedLoadbutton();
	afx_msg void OnBnClickedClearbutton();
	CListBox m_MenuDlgListCtrl;
	virtual BOOL OnInitDialog();
};
