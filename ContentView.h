#if !defined(AFX_CONTENTVIEW_H__97FE80B9_799E_4AA4_B920_B8076B565A23__INCLUDED_)
#define AFX_CONTENTVIEW_H__97FE80B9_799E_4AA4_B920_B8076B565A23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ContentView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CContentView view

class CContentView : public CListView
{
protected:
	CContentView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CContentView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContentView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CContentView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CContentView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTENTVIEW_H__97FE80B9_799E_4AA4_B920_B8076B565A23__INCLUDED_)
