// ContentView.cpp : implementation file
//

#include "stdafx.h"
#include "3eExplorer.h"
#include "ContentView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContentView

IMPLEMENT_DYNCREATE(CContentView, CListView)

CContentView::CContentView()
{
}

CContentView::~CContentView()
{
}


BEGIN_MESSAGE_MAP(CContentView, CListView)
	//{{AFX_MSG_MAP(CContentView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContentView drawing

void CContentView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CContentView diagnostics

#ifdef _DEBUG
void CContentView::AssertValid() const
{
	CListView::AssertValid();
}

void CContentView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CContentView message handlers
