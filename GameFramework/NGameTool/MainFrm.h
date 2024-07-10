
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once
#include "LeftView.h"
#include "RightView.h"

class CMYSP : public CSplitterWnd
{
public:
	CMYSP()
	{
		m_cxSplitterGap = 2;
		m_cySplitterGap = 2;

		m_cxBorderShare = 1;
		m_cyBorderShare = 1;

		m_cxBorder = 1;
		m_cyBorder = 1;
	}
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};



class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame() noexcept;
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CMYSP m_Sp;
	CRightView* m_RightView;
	CLeftView* m_LeftView;

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

};


