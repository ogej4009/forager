﻿#pragma once
#include "RightDlg.h"


// RView 폼 보기

class RView : public CFormView
{
	DECLARE_DYNCREATE(RView)

protected:
	RView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~RView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RView };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	RightDlg NewDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


