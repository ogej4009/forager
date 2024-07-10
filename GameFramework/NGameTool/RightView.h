#pragma once
#include "RightDlg.h"


// CRightView 폼 보기

class CRightView : public CFormView
{
	DECLARE_DYNCREATE(CRightView)

protected:
	CRightView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CRightView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RIGHTVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CRightDlg NewDlg;


public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


