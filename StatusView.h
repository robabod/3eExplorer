#if !defined(AFX_STATUSVIEW_H__A6B764BD_7164_46ED_A961_EFCE5F68C69A__INCLUDED_)
#define AFX_STATUSVIEW_H__A6B764BD_7164_46ED_A961_EFCE5F68C69A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatusView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatusView view

class CStatusView : public CListView
{
protected:
	CStatusView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CStatusView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CStatusView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CStatusView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSVIEW_H__A6B764BD_7164_46ED_A961_EFCE5F68C69A__INCLUDED_)
