// 3eExplorerView.cpp : implementation of the CMy3eExplorerView class
//

#include "stdafx.h"
#include "3eExplorer.h"

#include "3eExplorerDoc.h"
#include "3eExplorerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3eExplorerView

IMPLEMENT_DYNCREATE(CMy3eExplorerView, CMy3eExplorerViewBase)

BEGIN_MESSAGE_MAP(CMy3eExplorerView, CMy3eExplorerViewBase)
	//{{AFX_MSG_MAP(CMy3eExplorerView)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemExpanding)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelectionChanged)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EXPLORER_EXTRACT_TO_TAP, OnExplorerExtractToTap)
	ON_UPDATE_COMMAND_UI(ID_EXPLORER_EXTRACT_TO_TAP, OnUpdateExplorerExtractToTap)
	ON_UPDATE_COMMAND_UI(ID_EXPLORER_FILENAME, OnUpdateExplorerFilename)
	ON_UPDATE_COMMAND_UI(ID_EXPLORER_EXTRACT_TO_BIN, OnUpdateExplorerExtractToBin)
	ON_COMMAND(ID_EXPLORER_EXTRACT_TO_BIN, OnExplorerExtractToBin)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRClick)
	ON_UPDATE_COMMAND_UI(ID_EXPLORER_EXTRACT_TO_BIN_WITH_HEADER, OnUpdateExplorerExtractToBinWithHeader)
	ON_COMMAND(ID_EXPLORER_EXTRACT_TO_BIN_WITH_HEADER, OnExplorerExtractToBinWithHeader)
	//}}AFX_MSG_MAP
	ON_WM_INITMENUPOPUP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3eExplorerView construction/destruction

CMy3eExplorerView::CMy3eExplorerView()
: m_objActive(NULL)
, m_htActive(0)
{
	// map the possible type to their respective images
	m_ilmap[CTreeObject::INVALID] = 0;
	m_ilmap[CTreeObject::HDF] = 1;
	m_ilmap[CTreeObject::PARTITION_PLUSIDEDOS] = 2;
	m_ilmap[CTreeObject::PARTITION_PLUS3DOS] = 3;
	m_ilmap[CTreeObject::PLUS3DOS_USER_DIRECTORY] = 4;
	m_ilmap[CTreeObject::PLUS3DOS_USER_DIRECTORY_ERASED] = 5;
	m_ilmap[CTreeObject::PLUS3DOS_FILE] = 6;
	m_ilmap[CTreeObject::PLUS3DOS_FILE_ERASED] = 7;
	m_ilmap[CTreeObject::PLUS3DOS_FILE_PROGRAM] = 8;
	m_ilmap[CTreeObject::PLUS3DOS_FILE_NUMARRAY] = 9;
	m_ilmap[CTreeObject::PLUS3DOS_FILE_CHARARRAY] = 10;
	m_ilmap[CTreeObject::PLUS3DOS_FILE_CODE] = 11;
	m_ilmap[CTreeObject::PLUS3DOS_FILE_HEADERLESS] = 12;
	m_ilmap[CTreeObject::RESERVED] = 0;
}

CMy3eExplorerView::~CMy3eExplorerView()
{
}

BOOL CMy3eExplorerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if (!CMy3eExplorerViewBase::PreCreateWindow(cs))
		return FALSE;

	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_DISABLEDRAGDROP;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMy3eExplorerView drawing

void CMy3eExplorerView::OnDraw(CDC* pDC)
{
	CMy3eExplorerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMy3eExplorerView diagnostics

#ifdef _DEBUG
void CMy3eExplorerView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3eExplorerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3eExplorerDoc* CMy3eExplorerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3eExplorerDoc)));
	return (CMy3eExplorerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy3eExplorerView message handlers

void CMy3eExplorerView::OnInitialUpdate() 
{
	CMy3eExplorerViewBase::OnInitialUpdate();

	// set up the images
	m_ilImageList.Create(16, 15, ILC_COLOR24 | ILC_MASK, 1, 1);
	m_bmpImageList.LoadBitmap(IDB_TREE_ICONS);
	m_bmpImageListMask.LoadBitmap(IDB_TREE_ICONS_MASK);
	m_ilImageList.Add(&m_bmpImageList, &m_bmpImageListMask);

	GetTreeCtrl().SetImageList(&m_ilImageList, TVSIL_NORMAL);

	CMy3eExplorerDoc *pDoc = GetDocument();

	CHdfHeader *pHdf = pDoc->GetRoot();

	HTREEITEM hItem = GetTreeCtrl().InsertItem(pHdf->GetName().c_str(), m_ilmap[pHdf->Type()], m_ilmap[pHdf->Type()]);

	// set a couple things...
	GetTreeCtrl().SetItemData(hItem, (DWORD)pHdf);

	GetTreeCtrl().Select(hItem, TVGN_CARET);

	if (pHdf->IsExpandable())
	{
		// add a null item so we get the "expand" box...
		hItem = GetTreeCtrl().InsertItem(_T(""), m_ilmap[CTreeObject::INVALID], m_ilmap[CTreeObject::INVALID], hItem);
		GetTreeCtrl().SetItemData(hItem, 0);
	}

	pDoc->UpdateAllViews(this, 0x01, pHdf);
}

void CMy3eExplorerView::OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW *pNMTV = (NM_TREEVIEW*) pNMHDR;
	HTREEITEM hItem = pNMTV->itemNew.hItem;
	CTreeObject *pObj = (CTreeObject*)(GetTreeCtrl().GetItemData(hItem));

	ASSERT (NULL != pObj);

	// if we're expanding the tree, check to see if we need to parse the contents...
	if (NULL != pObj && TVE_EXPAND == pNMTV->action)
	{
		// if the first child has NULL data it means we've not parsed it yet.
		HTREEITEM hChildItem = GetTreeCtrl().GetChildItem(hItem);
		if (NULL != hChildItem)
		{
			DWORD item_data = GetTreeCtrl().GetItemData(hChildItem);
			if (NULL == item_data)
			{
				GetTreeCtrl().DeleteItem(hChildItem);

				// force the object to parse for any children
				pObj->ParseForChildren();

				// now loop through the child objects and add them...
				std::vector<CTreeObject *>::iterator it = pObj->GetChildren();
				while (pObj->GetChildrenEnd() != it)
				{
					CTreeObject * pChild = (*it);
					HTREEITEM hChild = GetTreeCtrl().InsertItem(pChild->GetName().c_str(), m_ilmap[pChild->Type()], m_ilmap[pChild->Type()], hItem);
					GetTreeCtrl().SetItemData(hChild, (DWORD)pChild);

					if (pChild->IsExpandable())
					{
						// add an expander. we should alter this to have an "expandable" flag
						hChild = GetTreeCtrl().InsertItem(_T(""), m_ilmap[CTreeObject::INVALID], m_ilmap[CTreeObject::INVALID], hChild);
						GetTreeCtrl().SetItemData(hChild, 0);
					}
					++it;
				}
			}
		}

	}
}

void CMy3eExplorerView::OnSelectionChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// the selection has changed, so update all the views with the new object.
	NM_TREEVIEW *pNMTV = (NM_TREEVIEW*) pNMHDR;

	// update the current item
	m_htActive = pNMTV->itemNew.hItem;
	m_objActive = (CTreeObject*)(GetTreeCtrl().GetItemData(m_htActive));

	GetDocument()->UpdateAllViews(this, 0x01, m_objActive);
}

void CMy3eExplorerView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// check to see if this was generated from the kb (Shift-F10)
	HTREEITEM htItem = NULL;

	if (-1 == point.x && -1 == point.y)
	{
		//point = (CPoint) GetMessagePos();
		// work out which item is selected...
		htItem = m_htActive;

		// ok, where is it on the screen?
		CRect rc;
		if (!GetTreeCtrl().GetItemRect(htItem, &rc, TRUE))
		{
			rc.SetRect(0, 0, 0, 0);
		}

		// ok, ensure the rect we have at least intersects the client area
		CRect client_rc;
		GetClientRect(&client_rc);

		if (rc.top < client_rc.top) rc.top = client_rc.top;
		if (rc.left < client_rc.left) rc.left = client_rc.left;

		if (rc.left > client_rc.Width()) rc.left = 0;
		if (rc.top > client_rc.Height()) rc.top = 0;

		// ok, we have a position in the control, now set the menu to pop up in the middle.
		point.x = rc.left;
		point.y = rc.top;
	}
	else
	{
		ScreenToClient(&point);

		UINT uFlags;
		htItem = GetTreeCtrl().HitTest(point, &uFlags);
	}

	if (NULL != htItem)
	{
		m_htActive = htItem;
		m_objActive = (CTreeObject*)(GetTreeCtrl().GetItemData(m_htActive));

		if (NULL != m_objActive)
		{
			CMenu menu;
			CMenu* pPopup;

			// which menu do we want?
			switch (m_objActive->Type())
			{
			case CTreeObject::PLUS3DOS_FILE:
			case CTreeObject::PLUS3DOS_FILE_PROGRAM:
			case CTreeObject::PLUS3DOS_FILE_NUMARRAY:
			case CTreeObject::PLUS3DOS_FILE_CHARARRAY:
			case CTreeObject::PLUS3DOS_FILE_CODE:
			case CTreeObject::PLUS3DOS_FILE_HEADERLESS:
				{
					menu.LoadMenu(IDR_EXPLORER_POPUP_FILE);
				}
				break;
			//case CTreeObject::PLUS3DOS_USER_DIRECTORY:
			//case CTreeObject::PLUS3DOS_USER_DIRECTORY_ERASED:
			//	{
			//		menu.LoadMenu(IDR_EXPLORER_POPUP_FILE);
			//	}
			//	break;
			default:
				{
					menu.LoadMenu(IDR_EXPLORER_POPUP);
				}
				break;
			}

			pPopup = menu.GetSubMenu(0);

			ClientToScreen(&point);
			pPopup->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
		}
	}
}

void CMy3eExplorerView::OnRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// generate the context-menu message to self
	SendMessage(WM_CONTEXTMENU, (WPARAM) m_hWnd, GetMessagePos());
	// stop this being handled again
	*pResult = 1;
}

void CMy3eExplorerView::OnExplorerExtractToTap() 
{
	if (NULL != m_objActive)
	{
		m_objActive->ExtractObject(CExplorerFile::TAPFILE);
	}
}


void CMy3eExplorerView::OnUpdateExplorerExtractToTap(CCmdUI* pCmdUI) 
{
	if (NULL != m_objActive && m_objActive->IsExtractable())
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CMy3eExplorerView::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	// Annoyingly, we need to handle this and do what the FrameWnd would do,
	// otherwise we won't get the ON_UPDATE_COMMAND_UI calls.

	ASSERT(NULL != pPopupMenu);

	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT (NULL == state.m_pOther);
	ASSERT (NULL == state.m_pParentMenu);

	// is this a popup in top-level menu?
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
	{
		// set parent = child
		state.m_pParentMenu = pPopupMenu;
	}
	else if (NULL != (hParentMenu = ::GetMenu(m_hWnd)))
	{
		CWnd *pParent = this;
		if (NULL != pParent && NULL != (hParentMenu = ::GetMenu(pParent->m_hWnd)))
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
				{
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}

	// ok, done that stuff...
	// now let's go through the actual menu items
	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();

	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax; state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (0 == state.m_nID)
			continue;

		ASSERT(NULL == state.m_pOther);
		ASSERT(NULL != state.m_pMenu);

		if ((UINT)-1 == state.m_nID)
		{
			// possibly a popup
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
			if (NULL == state.m_pSubMenu ||
				0 == (state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) ||
				(UINT)-1 == state.m_nID)
			{
				continue;
			}
			state.DoUpdate(this, TRUE);
		}
		else
		{
			// normal menu item
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, FALSE);
		}

		// adjust for menu additions and deletions
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}

		state.m_nIndexMax = nCount;
	}
}

void CMy3eExplorerView::OnUpdateExplorerFilename(CCmdUI* pCmdUI) 
{
	if (NULL != m_objActive)
		pCmdUI->SetText(m_objActive->GetName().c_str());
	pCmdUI->Enable(FALSE);
}

void CMy3eExplorerView::OnUpdateExplorerExtractToBin(CCmdUI* pCmdUI) 
{
	if (NULL != m_objActive && m_objActive->IsExtractable())
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CMy3eExplorerView::OnExplorerExtractToBin() 
{
	if (NULL != m_objActive)
	{
		m_objActive->ExtractObject(CExplorerFile::BINFILE);
	}
}

void CMy3eExplorerView::OnUpdateExplorerExtractToBinWithHeader(CCmdUI* pCmdUI) 
{
	if (NULL != m_objActive && m_objActive->IsExtractable() && CTreeObject::PLUS3DOS_FILE_HEADERLESS != m_objActive->Type())
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CMy3eExplorerView::OnExplorerExtractToBinWithHeader() 
{
	if (NULL != m_objActive)
	{
		m_objActive->ExtractObject(CExplorerFile::BINFILE, true);
	}
}
