// DetailView.cpp : implementation file
//

#include "stdafx.h"
#include "3eExplorer.h"
#include "DetailView.h"

#include "TreeObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDetailView

IMPLEMENT_DYNCREATE(CDetailView, CEditView)

CDetailView::CDetailView()
{
}

CDetailView::~CDetailView()
{
}


BEGIN_MESSAGE_MAP(CDetailView, CEditView)
	//{{AFX_MSG_MAP(CDetailView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDetailView drawing

void CDetailView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CDetailView diagnostics

#ifdef _DEBUG
void CDetailView::AssertValid() const
{
	CEditView::AssertValid();
}

void CDetailView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDetailView message handlers

void CDetailView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (lHint)
	{
		CTreeObject *pObj = (CTreeObject*)pHint;

		// wipe the text.
		GetEditCtrl().SetWindowText(_T("No Information Available"));

		if (NULL != pObj)
		{
			GetEditCtrl().SetWindowText(pObj->GetInformation().c_str());
		}
	}
}

int CDetailView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// set the editbox to be fixed-width text for now
	LOGFONT lf;
	::GetObject(GetStockObject(ANSI_FIXED_FONT), sizeof(LOGFONT), &lf);
	m_cFont.CreateFontIndirect(&lf);
	SetFont(&m_cFont);

	return 0;
}
