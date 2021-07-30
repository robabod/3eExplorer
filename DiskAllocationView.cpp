// DiskAllocationView.cpp : implementation file
//

#include "stdafx.h"
#include "3eExplorer.h"
#include "DiskAllocationView.h"
#include "3eExplorerDoc.h"
#include "memdc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiskAllocationView

IMPLEMENT_DYNCREATE(CDiskAllocationView, CScrollView)

CDiskAllocationView::CDiskAllocationView()
: m_objActive(NULL)
, m_csBlockScale(3,4)
{
}

CDiskAllocationView::~CDiskAllocationView()
{
}


BEGIN_MESSAGE_MAP(CDiskAllocationView, CScrollView)
	//{{AFX_MSG_MAP(CDiskAllocationView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiskAllocationView drawing

void CDiskAllocationView::OnDraw(CDC* pDC)
{
	//CMemDC DC(pDC);

	CMy3eExplorerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// work out how big our grid should be (from the CHS)
	CCHS chs;
	pDoc->GetRoot()->getCHS(chs);

	// how much are we updating?
	CRect rcClip;
	pDC->GetClipBox(&rcClip);
	//rcClip.OffsetRect(-m_ptBlockOffset);

	unsigned int cyl_start = rcClip.top / m_csBlockScale.cy;
	unsigned int cyl_end   = (rcClip.top + rcClip.Height()) / m_csBlockScale.cy;

	unsigned int blk_start = rcClip.left / m_csBlockScale.cx;
	unsigned int blk_end   = (rcClip.left + rcClip.Width()) / m_csBlockScale.cx;

	// alter the end to ensure we're drawing everything.
	// it really doesn't matter if we overshoot... better than under, eh?
	//cyl_end += 8;
	//blk_end += 8;

	// check to see if we're drawing everything...
	if (cyl_end > chs.c)
		cyl_end = chs.c;
	if (blk_end > (chs.h * chs.s))
		blk_end = (chs.h * chs.s);

	// set up our brushes...
	CBrush block_empty(RGB(0xf0, 0xf0, 0xf0));
	CBrush block_full(RGB(0xf0, 0x00, 0x00));
	CPen   border_empty(PS_SOLID, 1, RGB(0xe0, 0xe0, 0xe0));
	CPen   border_full(PS_SOLID, 1, RGB(0xe0, 0x00, 0x00));
	CBrush *pold_brush;
	CPen   *pold_pen;

	// now step through each block and draw it...
	for (int cur_cyl = cyl_start; cur_cyl <= cyl_end; cur_cyl++)
	{
		for (int cur_blk = blk_start; cur_blk <= blk_end; cur_blk++)
		{
			// draw the rectangle
			CPoint pt(m_csBlockScale.cx * cur_blk, m_csBlockScale.cy * cur_cyl);
			CRect rc(pt, m_csBlockScale);
			pold_brush = pDC->SelectObject(&block_empty);
			pold_pen   = pDC->SelectObject(&border_empty);

			pDC->FillRect(rc, &block_empty);
			pDC->MoveTo(rc.right - 1, rc.top);
			pDC->LineTo(rc.right - 1, rc.bottom - 1);
			pDC->LineTo(rc.left, rc.bottom - 1);

			pDC->SelectObject(pold_brush);
			pDC->SelectObject(pold_pen);
		}
	}

	block_empty.DeleteObject();
	block_full.DeleteObject();
	border_empty.DeleteObject();
	border_full.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// CDiskAllocationView diagnostics

#ifdef _DEBUG
void CDiskAllocationView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDiskAllocationView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMy3eExplorerDoc* CDiskAllocationView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3eExplorerDoc)));
	return (CMy3eExplorerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiskAllocationView message handlers

void CDiskAllocationView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (lHint)
	{
		CTreeObject *pObj = (CTreeObject*)pHint;

		if (NULL != pObj)
		{
			m_objActive = pObj;

			// set the scroll sizes...
			CMy3eExplorerDoc* pDoc = GetDocument();
			CCHS chs;
			pDoc->GetRoot()->getCHS(chs);
			SetScrollSizes(MM_TEXT, CSize((m_csBlockScale.cx * ((chs.h * chs.s))), (m_csBlockScale.cy * (chs.c))));

			Invalidate(FALSE);
		}
	}
}


BOOL CDiskAllocationView::OnEraseBkgnd(CDC* pDC) 
{
	return CScrollView::OnEraseBkgnd(pDC);
	//return FALSE;
}
