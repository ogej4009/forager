#pragma once


// CMapMenuDlg 대화 상자

class CMapMenuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMapMenuDlg)

public:
	CMapMenuDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMapMenuDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPMENUDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedSavebtn();
	afx_msg void OnBnClickedLoadbtn();
	
	afx_msg void OnBnClickedClearbtn();
	CListBox mapObjList;
	afx_msg void OnLbnSelchangeMapobjlist();
	virtual BOOL OnInitDialog();
};
