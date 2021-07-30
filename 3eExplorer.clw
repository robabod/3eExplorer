; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDocumentStatus
LastTemplate=CListView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "3eExplorer.h"
LastPage=0

ClassCount=12
Class1=CMy3eExplorerApp
Class2=CMy3eExplorerDoc
Class3=CMy3eExplorerView
Class4=CMainFrame

ResourceCount=10
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_MY3EEXTYPE
Class5=CChildFrame
Class6=CAboutDlg
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDR_EXPLORER_POPUP_FILE
Class7=CDetailView
Class8=CContentView
Resource6=IDR_EXPLORER_POPUP
Resource7=IDR_MY3EEXTYPE (English (U.S.))
Class9=COptionsDialog
Resource8=IDR_MAINFRAME (English (U.S.))
Class10=CDiskAllocationView
Resource9=IDD_OPTIONS
Class11=CDocumentStatus
Class12=CStatusView
Resource10=IDD_STATUS

[CLS:CMy3eExplorerApp]
Type=0
HeaderFile=3eExplorer.h
ImplementationFile=3eExplorer.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CMy3eExplorerApp

[CLS:CMy3eExplorerDoc]
Type=0
HeaderFile=3eExplorerDoc.h
ImplementationFile=3eExplorerDoc.cpp
Filter=N
LastObject=ID_FILE_FILESTATUS
BaseClass=CDocument
VirtualFilter=DC

[CLS:CMy3eExplorerView]
Type=0
HeaderFile=3eExplorerView.h
ImplementationFile=3eExplorerView.cpp
Filter=C
LastObject=CMy3eExplorerView
BaseClass=CMy3eExplorerViewBase
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
LastObject=CChildFrame
BaseClass=CMDIChildWnd
VirtualFilter=mfWC


[CLS:CAboutDlg]
Type=0
HeaderFile=3eExplorer.cpp
ImplementationFile=3eExplorer.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7
Command3=ID_FILE_MRU_FILE1

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
CommandCount=8
Command8=ID_APP_ABOUT

[MNU:IDR_MY3EEXTYPE]
Type=1
Class=CMy3eExplorerView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_WINDOW_NEW
CommandCount=18
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command15=ID_WINDOW_CASCADE
Command16=ID_WINDOW_TILE_HORZ
Command17=ID_WINDOW_ARRANGE
Command18=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
CommandCount=13
Command4=ID_EDIT_UNDO
Command13=ID_PREV_PANE


[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_VIEW_OPTIONS
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MY3EEXTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_FILESTATUS
Command7=ID_FILE_MRU_FILE1
Command8=ID_APP_EXIT
Command9=ID_EXPLORER_EXTRACT_TO_TAP
Command10=ID_EXPLORER_EXTRACT_TO_BIN
Command11=ID_EXPLORER_EXTRACT_TO_BIN_WITH_HEADER
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_VIEW_TOOLBAR
Command17=ID_VIEW_STATUS_BAR
Command18=ID_VIEW_OPTIONS
Command19=ID_WINDOW_NEW
Command20=ID_WINDOW_CASCADE
Command21=ID_WINDOW_TILE_HORZ
Command22=ID_WINDOW_ARRANGE
Command23=ID_WINDOW_SPLIT
Command24=ID_APP_ABOUT
CommandCount=24

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=2
Control1=IDOK,button,1342373889
Control2=IDC_ABOUT_TEXT,edit,1342245060

[DLG:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
ControlCount=0

[CLS:CDetailView]
Type=0
HeaderFile=DetailView.h
ImplementationFile=DetailView.cpp
BaseClass=CEditView
Filter=C
VirtualFilter=VWC
LastObject=CDetailView

[CLS:CContentView]
Type=0
HeaderFile=ContentView.h
ImplementationFile=ContentView.cpp
BaseClass=CListView
Filter=C

[DLG:IDD_OPTIONS]
Type=1
Class=COptionsDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_PRECACHE_TRACK,button,1342242819
Control4=IDC_PRE_READ_HEADER,button,1342242819

[CLS:COptionsDialog]
Type=0
HeaderFile=OptionsDialog.h
ImplementationFile=OptionsDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=COptionsDialog

[MNU:IDR_EXPLORER_POPUP_FILE]
Type=1
Class=?
Command1=ID_EXPLORER_FILENAME
Command2=ID_EXPLORER_EXTRACT_TO_TAP
Command3=ID_EXPLORER_EXTRACT_TO_BIN
Command4=ID_EXPLORER_EXTRACT_TO_BIN_WITH_HEADER
CommandCount=4

[MNU:IDR_EXPLORER_POPUP]
Type=1
Class=?
Command1=ID_EXPLORER_FILENAME
CommandCount=1

[CLS:CDiskAllocationView]
Type=0
HeaderFile=DiskAllocationView.h
ImplementationFile=DiskAllocationView.cpp
BaseClass=CScrollView
Filter=C
LastObject=CDiskAllocationView
VirtualFilter=VWC

[DLG:IDD_STATUS]
Type=1
Class=CDocumentStatus
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_FLUSH_CACHE,button,1342242816
Control3=IDC_STATUS_LISTBOX,listbox,1352728961

[CLS:CDocumentStatus]
Type=0
HeaderFile=DocumentStatus.h
ImplementationFile=DocumentStatus.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_FLUSH_CACHE

[CLS:CStatusView]
Type=0
HeaderFile=StatusView.h
ImplementationFile=StatusView.cpp
BaseClass=CListView
Filter=C

