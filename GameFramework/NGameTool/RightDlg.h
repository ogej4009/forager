#pragma once
#include <vector>
#include <GameMath.h>

// CRightDlg 대화 상자

class CRightDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRightDlg)

public:
	CRightDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CRightDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RIGHTVIEWDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	std::vector<CDialogEx*> ArrDlg;

public:
	template<typename T>
	void NCreateDlg(unsigned int _ID)
	{
		T* NewDlg = new T();
		NewDlg->Create(_ID, &TabMenu);
		NewDlg->ShowWindow(SW_HIDE);
		NewDlg->SetBackgroundColor(RGB(200, 200, 200));
		NewDlg->SetWindowPos(nullptr, 4, 20, 500, 500, 0);
		ArrDlg.push_back(NewDlg);
	}



public:
	CTabCtrl TabMenu;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTcnSelchangeToolmenu(NMHDR *pNMHDR, LRESULT *pResult);
};
