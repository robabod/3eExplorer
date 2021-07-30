#if !defined(AFX_DETAILVIEW_H__595342D4_1BA8_4E65_82E4_537126CB8A84__INCLUDED_)
#define AFX_DETAILVIEW_H__595342D4_1BA8_4E65_82E4_537126CB8A84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DetailView.h : header file
//

#include "TreeObject.h"
#include "HdfHeader.h"
#include "IDEDOS_SystemPartition.h"


/////////////////////////////////////////////////////////////////////////////
// CDetailView view

#define CDetailViewBase CEditView

class CDetailView : public CDetailViewBase
{
protected:
	CDetailView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDetailView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDetailView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDetailView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	CFont m_cFont;

	//{{AFX_MSG(CDetailView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DETAILVIEW_H__595342D4_1BA8_4E65_82E4_537126CB8A84__INCLUDED_)
