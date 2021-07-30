// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "3eExplorer.h"

#include "ChildFrm.h"

#include "3eExplorerView.h"
#include "DetailView.h"
#include "ContentView.h"
#include "StatusView.h"
#include "DiskAllocationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::OnCreateClient( LPCREATESTRUCT lpcs,
	CCreateContext* pContext)
{
	// work out the sizes according to the client size.
	int explorerview_cx = 256;
	int contentview_cy = lpcs->cy / 2;

	if (lpcs->cx < 512)
	{
		explorerview_cx = lpcs->cx / 2;
	}

	if (!m_wndSplitter.CreateStatic(this, 1, 2) ||
		!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMy3eExplorerView), CSize(explorerview_cx, 0), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CDetailView), CSize(0, 0), pContext))
		return FALSE;
	else
		return TRUE;

	//if (!m_wndSplitter.CreateStatic(this, 1, 2) ||
	//	!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMy3eExplorerView), CSize(explorerview_cx, 0), pContext) ||
	//	!m_wndSplitterSub1.CreateStatic(&m_wndSplitter, 2, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter.IdFromRowCol(0, 1)) ||
	//	!m_wndSplitterSub1.CreateView(0, 0, RUNTIME_CLASS(CDetailView), CSize(0, contentview_cy), pContext) ||
	//	!m_wndSplitterSub1.CreateView(1, 0, RUNTIME_CLASS(CStatusView), CSize(0, contentview_cy), pContext))
	//	return FALSE;
	//else
	//	return TRUE;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	return TRUE;
}

void CChildFrame::ActivateFrame(int nCmdShow)
{
	// TODO: Modify this function to change how the frame is activated.

	nCmdShow = SW_SHOWMAXIMIZED;
	CMDIChildWnd::ActivateFrame(nCmdShow);
}


/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIChildWnd::OnSize(nType, cx, cy);
}
