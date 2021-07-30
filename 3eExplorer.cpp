// 3eExplorer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "3eExplorer.h"

#include "ChildFrm.h"
#include "3eExplorerDoc.h"
#include "3eExplorerView.h"
#include "registry.h"
#include "OptionsDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3eExplorerApp

BEGIN_MESSAGE_MAP(CMy3eExplorerApp, CWinApp)
	//{{AFX_MSG_MAP(CMy3eExplorerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OPTIONS, OnUpdateViewOptions)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_COMMAND(ID_VIEW_OPTIONS, OnViewOptions)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3eExplorerApp construction

CMy3eExplorerApp::CMy3eExplorerApp()
: m_bHeadCache(FALSE)
, m_bPreReadFileInfo(TRUE)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMy3eExplorerApp object

CMy3eExplorerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMy3eExplorerApp initialization

BOOL CMy3eExplorerApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(REG_ROOT);

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	LoadGlobalSettings();

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_MY3EEXTYPE,
		RUNTIME_CLASS(CMy3eExplorerDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CMy3eExplorerView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainFrame = pMainFrame;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CString m_strAbout;
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_strAbout = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_ABOUT_TEXT, m_strAbout);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMy3eExplorerApp::OnAppAbout()
{
	// build some information about this application into a string
	std::ostringstream ostr;
	char filename[_MAX_PATH];
	GetModuleFileName(NULL, filename, _MAX_PATH);
	std::string fnstr = filename;
	int last_pos = fnstr.find_last_of(_T("\\/"));
	if (std::string::npos == last_pos)
		last_pos = 0;
	else
		last_pos ++;
	ostr << fnstr.substr(last_pos) << "\r\n";

	DWORD dwTmp;
	DWORD dwSize = GetFileVersionInfoSize(filename, &dwTmp);
	void *versionInfo = new char[dwSize];

	if (GetFileVersionInfo(filename, dwTmp, dwSize, versionInfo))
	{
		LPVOID lpBuffer;
		UINT uiBuffer;
		CString strtmp;

		VerQueryValue(versionInfo, _T("\\StringFileInfo\\040904B0\\FileDescription"), &lpBuffer, &uiBuffer);
		ostr << (LPCTSTR)lpBuffer << _T("\r\n");

		VerQueryValue(versionInfo, _T("\\StringFileInfo\\040904B0\\ProductVersion"), &lpBuffer, &uiBuffer);
		strtmp = (LPCTSTR)lpBuffer;
		strtmp.Replace(_T(", "), _T("."));
		ostr << _T("Version: ") << (LPCTSTR)strtmp;
		#ifdef _DEBUG
		ostr << "_DEBUG";
		#endif _DEBUG
		ostr << _T("\r\n");

		VerQueryValue(versionInfo, _T("\\StringFileInfo\\040904B0\\LegalCopyright"), &lpBuffer, &uiBuffer);
		ostr << (LPCTSTR)lpBuffer;
	}
	else
	{
		ostr << "Error - cannot get version information";
	}

	delete [] versionInfo;

	CAboutDlg aboutDlg;
	aboutDlg.m_strAbout = ostr.str().c_str();
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMy3eExplorerApp message handlers

void CMy3eExplorerApp::LoadGlobalSettings()
{
	// this method loads the global settings from the Registry
	if (GetProfileInt(REG_SETTINGS, REG_SETTINGS_HEADCACHE, 0))
		m_bHeadCache = TRUE;
	else
		m_bHeadCache = FALSE;

	if (GetProfileInt(REG_SETTINGS, REG_SETTINGS_PREREADFILEINFO, 1))
		m_bPreReadFileInfo = TRUE;
	else
		m_bPreReadFileInfo = FALSE;
}

void CMy3eExplorerApp::SaveGlobalSettings()
{
	// this method saves the global settings to the Registry
	WriteProfileInt(REG_SETTINGS, REG_SETTINGS_HEADCACHE, m_bHeadCache ? 1 : 0);
	WriteProfileInt(REG_SETTINGS, REG_SETTINGS_PREREADFILEINFO, m_bPreReadFileInfo ? 1 : 0);
}

int CMy3eExplorerApp::ExitInstance() 
{
	SaveGlobalSettings();
	return CWinApp::ExitInstance();
}

void CMy3eExplorerApp::OnUpdateViewOptions(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
}

void CMy3eExplorerApp::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
}

void CMy3eExplorerApp::OnViewOptions() 
{
	// Display the options dialog
	COptionsDialog optionsDlg;
	optionsDlg.m_bPreCacheHeader = m_bPreReadFileInfo;
	optionsDlg.m_bPreCacheTrack  = m_bHeadCache;
	optionsDlg.DoModal();
	m_bPreReadFileInfo = optionsDlg.m_bPreCacheHeader;
	m_bHeadCache = optionsDlg.m_bPreCacheTrack;
}
