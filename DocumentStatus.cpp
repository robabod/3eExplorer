// DocumentStatus.cpp : implementation file
//

#include "stdafx.h"
#include "3eExplorer.h"
#include "DocumentStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocumentStatus dialog


CDocumentStatus::CDocumentStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDocumentStatus::IDD, pParent)
	, m_pExplorerDoc(NULL)
{
	//{{AFX_DATA_INIT(CDocumentStatus)
	//}}AFX_DATA_INIT
}


void CDocumentStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDocumentStatus)
	DDX_Control(pDX, IDC_STATUS_LISTBOX, m_Listbox);
	//}}AFX_DATA_MAP

	SetStatusInformation();
}


BEGIN_MESSAGE_MAP(CDocumentStatus, CDialog)
	//{{AFX_MSG_MAP(CDocumentStatus)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_FLUSH_CACHE, OnFlushCache)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDocumentStatus message handlers


int CDocumentStatus::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (NULL != m_pExplorerDoc)
	{
		SetWindowText(m_pExplorerDoc->GetRoot()->GetName().c_str());
	}

	return 0;
}

void CDocumentStatus::SetStatusInformation()
{
	// remove the items from the listbox...
	while (m_Listbox.GetCount())
	{
		m_Listbox.DeleteString(0);
	}

	if (NULL != m_pExplorerDoc)
	{
		m_Listbox.SetTabStops(100);

		std::ostringstream ostr;
		ostr << "Cylinders\t" << m_pExplorerDoc->GetRoot()->getCylinders();
		m_Listbox.AddString(ostr.str().c_str());
		ostr.str("");

		ostr << "Heads/Tracks\t" << m_pExplorerDoc->GetRoot()->getHeads();
		m_Listbox.AddString(ostr.str().c_str());
		ostr.str("");

		ostr << "Sectors\t" << m_pExplorerDoc->GetRoot()->getSectors();
		m_Listbox.AddString(ostr.str().c_str());
		ostr.str("");

		ostr << "Sector Size\t" << m_pExplorerDoc->GetRoot()->getSectorSize();
		m_Listbox.AddString(ostr.str().c_str());
		ostr.str("");

		ostr << "Sectors Cached\t" << m_pExplorerDoc->GetCacheSize();
		m_Listbox.AddString(ostr.str().c_str());
		ostr.str("");

		ostr << "Cache Memory\t" << (m_pExplorerDoc->GetCacheSize() * m_pExplorerDoc->GetRoot()->getSectorSize()) << "b";
		m_Listbox.AddString(ostr.str().c_str());
	}
}

void CDocumentStatus::OnFlushCache() 
{
	if (NULL != m_pExplorerDoc)
	{
		m_pExplorerDoc->FlushCache();
		SetStatusInformation();
	}
}
