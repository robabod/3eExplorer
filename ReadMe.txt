========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : 3eExplorer
========================================================================


AppWizard has created this 3eExplorer application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your 3eExplorer application.

3eExplorer.dsp
    This file (the project file) contains information at the project level and
    is used to build a single project or subproject. Other users can share the
    project (.dsp) file, but they should export the makefiles locally.

3eExplorer.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CMy3eExplorerApp application class.

3eExplorer.cpp
    This is the main application source file that contains the application
    class CMy3eExplorerApp.

3eExplorer.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
	Visual C++.

3eExplorer.clw
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

res\3eExplorer.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file 3eExplorer.rc.

res\3eExplorer.rc2
    This file contains resources that are not edited by Microsoft 
	Visual C++.  You should place all resources not editable by
	the resource editor in this file.



/////////////////////////////////////////////////////////////////////////////

For the main frame window:

MainFrm.h, MainFrm.cpp
    These files contain the frame class CMainFrame, which is derived from
    CMDIFrameWnd and controls all MDI frame features.

res\Toolbar.bmp
    This bitmap file is used to create tiled images for the toolbar.
    The initial toolbar and status bar are constructed in the CMainFrame
    class. Edit this toolbar bitmap using the resource editor, and
    update the IDR_MAINFRAME TOOLBAR array in 3eExplorer.rc to add
    toolbar buttons.
/////////////////////////////////////////////////////////////////////////////

For the child frame window:

ChildFrm.h, ChildFrm.cpp
    These files define and implement the CChildFrame class, which
    supports the child windows in an MDI application.

/////////////////////////////////////////////////////////////////////////////

AppWizard creates one document type and one view:

3eExplorerDoc.h, 3eExplorerDoc.cpp - the document
    These files contain your CMy3eExplorerDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CMy3eExplorerDoc::Serialize).

3eExplorerView.h, 3eExplorerView.cpp - the view of the document
    These files contain your CMy3eExplorerView class.
    CMy3eExplorerView objects are used to view CMy3eExplorerDoc objects.

res\3eExplorerDoc.ico
    This is an icon file, which is used as the icon for MDI child windows
    for the CMy3eExplorerDoc class.  This icon is included by the main
    resource file 3eExplorer.rc.


/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named 3eExplorer.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, and your application is 
in a language other than the operating system's current language, you
will need to copy the corresponding localized resources MFC42XXX.DLL
from the Microsoft Visual C++ CD-ROM onto the system or system32 directory,
and rename it to be MFCLOC.DLL.  ("XXX" stands for the language abbreviation.
For example, MFC42DEU.DLL contains resources translated to German.)  If you
don't do this, some of the UI elements of your application will remain in the
language of the operating system.

/////////////////////////////////////////////////////////////////////////////
