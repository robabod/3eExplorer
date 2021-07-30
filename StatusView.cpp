// StatusView.cpp : implementation file
//

#include "stdafx.h"
#include "3eExplorer.h"
#include "StatusView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusView

IMPLEMENT_DYNCREATE(CStatusView, CListView)

CStatusView::CStatusView()
{
}

CStatusView::~CStatusView()
{
}


BEGIN_MESSAGE_MAP(CStatusView, CListView)
	//{{AFX_MSG_MAP(CStatusView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusView drawing

void CStatusView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CStatusView diagnostics

#ifdef _DEBUG
void CStatusView::AssertValid() const
{
	CListView::AssertValid();
}

void CStatusView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusView message handlers
