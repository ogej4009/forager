// RView.cpp: 구현 파일
//

#include "pch.h"
#include "GameTool.h"
#include "RView.h"


// RView

IMPLEMENT_DYNCREATE(RView, CFormView)

RView::RView()
	: CFormView(IDD_RView)
{

}

RView::~RView()
{
}

void RView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(RView, CFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// RView 진단

#ifdef _DEBUG
void RView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void RView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// RView 메시지 처리기


int RView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	NewDlg.Create(IDD_RightDlg, this);
	NewDlg.ShowWindow(SW_SHOW);

	return 0;
}
