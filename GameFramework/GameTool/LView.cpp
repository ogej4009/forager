// LView.cpp: 구현 파일
//

#include "pch.h"
#include "GameTool.h"
#include "LView.h"
#include <GameWin.h>
#include <GameDevice.h>

// LView

IMPLEMENT_DYNCREATE(LView, CFormView)

LView::LView()
	: CFormView(IDD_LView)
{

}

LView::~LView()
{
}

void LView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(LView, CFormView)
END_MESSAGE_MAP()


// LView 진단

#ifdef _DEBUG
void LView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void LView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// LView 메시지 처리기


BOOL LView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//int HResult = CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	//return HResult;

	S_Ptr<GameWin> NewWin = GameWin::AddGameWin(L"TOOLLEFTVIEW", m_hWnd);
	GameDevice::CreateDevice(NewWin);
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
