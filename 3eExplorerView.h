// 3eExplorerView.h : interface of the CMy3eExplorerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_3EEXPLORERVIEW_H__5BADFA8E_4E79_41B7_84F2_F99FA85F1E1E__INCLUDED_)
#define AFX_3EEXPLORERVIEW_H__5BADFA8E_4E79_41B7_84F2_F99FA85F1E1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "3eExplorerDoc.h"


#define CMy3eExplorerViewBase CTreeView


class CMy3eExplorerView : public CMy3eExplorerViewBase
{
protected: // create from serialization only
	CMy3eExplorerView();
	DECLARE_DYNCREATE(CMy3eExplorerView)

// Attributes
public:
	CMy3eExplorerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3eExplorerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu);
	void OnRClick(NMHDR* pNMHDR, LRESULT* pResult);
	virtual ~CMy3eExplorerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CImageList m_ilImageList;
	CBitmap m_bmpImageList;
	CBitmap m_bmpImageListMask;
	CBitmap m_bmpImageList_Selected;
	std::map<CTreeObject::TreeObjectType, int> m_ilmap;

	HTREEITEM m_htActive;
	CTreeObject *m_objActive;

	//{{AFX_MSG(CMy3eExplorerView)
	afx_msg void OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelectionChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnExplorerExtractToTap();
	afx_msg void OnUpdateExplorerExtractToTap(CCmdUI* pCmdUI);
	afx_msg void OnUpdateExplorerFilename(CCmdUI* pCmdUI);
	afx_msg void OnUpdateExplorerExtractToBin(CCmdUI* pCmdUI);
	afx_msg void OnExplorerExtractToBin();
	afx_msg void OnUpdateExplorerExtractToBinWithHeader(CCmdUI* pCmdUI);
	afx_msg void OnExplorerExtractToBinWithHeader();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 3eExplorerView.cpp
inline CMy3eExplorerDoc* CMy3eExplorerView::GetDocument()
   { return (CMy3eExplorerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3EEXPLORERVIEW_H__5BADFA8E_4E79_41B7_84F2_F99FA85F1E1E__INCLUDED_)
