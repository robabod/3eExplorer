// 3eExplorer.h : main header file for the 3EEXPLORER application
//

#if !defined(AFX_3EEXPLORER_H__917076D4_9D4D_45D0_9DE1_40AAB7FE0C40__INCLUDED_)
#define AFX_3EEXPLORER_H__917076D4_9D4D_45D0_9DE1_40AAB7FE0C40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CMy3eExplorerApp:
// See 3eExplorer.cpp for the implementation of this class
//

class CMy3eExplorerApp : public CWinApp
{
public:
	CMy3eExplorerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3eExplorerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMy3eExplorerApp)
	afx_msg void OnAppAbout();
	afx_msg void OnUpdateViewOptions(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnViewOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	BOOL m_bHeadCache;
	BOOL m_bPreReadFileInfo;
	void SaveGlobalSettings();
	void LoadGlobalSettings();

public:
	CMainFrame *m_pMainFrame;

public:
	inline BOOL HeadCache() {return m_bHeadCache;};
	inline BOOL PreReadFileInfo() {return m_bPreReadFileInfo;};
};


extern CMy3eExplorerApp theApp;


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3EEXPLORER_H__917076D4_9D4D_45D0_9DE1_40AAB7FE0C40__INCLUDED_)
