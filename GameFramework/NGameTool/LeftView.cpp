// LeftView.cpp: 구현 파일
//

#include "pch.h"
#include "NGameTool.h"
#include "LeftView.h"
#include <GameWin.h>
#include <GameDevice.h>


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CFormView)

CLeftView::CLeftView()
	: CFormView(IDD_LEFTVIEW)
{

}

CLeftView::~CLeftView()
{
}



BEGIN_MESSAGE_MAP(CLeftView, CFormView)
END_MESSAGE_MAP()


// CLeftView 진단

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftView 메시지 처리기


BOOL CLeftView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	int HResult = CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

	CPTR<CGameWin> PTR = CGameWin::AddNGameWin(L"TOOLLEFTVIEW", m_hWnd);

	CGameDevice::CreateDevice(PTR);

	return HResult;
}
