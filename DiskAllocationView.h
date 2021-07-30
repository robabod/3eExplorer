#if !defined(AFX_DISKALLOCATIONVIEW_H__51F9CB92_E1DC_4950_9652_26D0A956EC8D__INCLUDED_)
#define AFX_DISKALLOCATIONVIEW_H__51F9CB92_E1DC_4950_9652_26D0A956EC8D__INCLUDED_

#include "TreeObject.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DiskAllocationView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDiskAllocationView view

class CDiskAllocationView : public CScrollView
{
protected:
	CDiskAllocationView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDiskAllocationView)

// Attributes
public:
	CMy3eExplorerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiskAllocationView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDiskAllocationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	const CSize m_csBlockScale;
	CTreeObject *m_objActive;
	//{{AFX_MSG(CDiskAllocationView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#ifndef _DEBUG  // debug version in CDiskAllocationView.cpp
inline CMy3eExplorerDoc* CDiskAllocationView::GetDocument()
   { return (CMy3eExplorerDoc*)m_pDocument; }
#endif


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISKALLOCATIONVIEW_H__51F9CB92_E1DC_4950_9652_26D0A956EC8D__INCLUDED_)
