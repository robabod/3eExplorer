#if !defined(AFX_DOCUMENTSTATUS_H__B118BD26_9EB6_4F26_8075_C93218EE4BDE__INCLUDED_)
#define AFX_DOCUMENTSTATUS_H__B118BD26_9EB6_4F26_8075_C93218EE4BDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DocumentStatus.h : header file
//

#include "3eExplorerDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CDocumentStatus dialog

class CDocumentStatus : public CDialog
{
// Construction
public:
	void SetExplorerDoc(CMy3eExplorerDoc *_pDoc) {m_pExplorerDoc = _pDoc;};
	CDocumentStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDocumentStatus)
	enum { IDD = IDD_STATUS };
	CListBox	m_Listbox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocumentStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetStatusInformation();
	CMy3eExplorerDoc * m_pExplorerDoc;

	// Generated message map functions
	//{{AFX_MSG(CDocumentStatus)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFlushCache();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCUMENTSTATUS_H__B118BD26_9EB6_4F26_8075_C93218EE4BDE__INCLUDED_)
