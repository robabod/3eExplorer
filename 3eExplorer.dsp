# Microsoft Developer Studio Project File - Name="3eExplorer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=3eExplorer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "3eExplorer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "3eExplorer.mak" CFG="3eExplorer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "3eExplorer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "3eExplorer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "3eExplorer - Win32 Release Static" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "3eExplorer - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release_Obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /profile
# Begin Custom Build
OutDir=.\Release
ProjDir=.
InputPath=.\Release\3eExplorer.exe
SOURCE="$(InputPath)"

"$(OutDir)\3eExplorer.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\3eExplorer.txt" "$(OutDir)" /y 
	date /t >> "$(OutDir)\3eExplorer.txt" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "3eExplorer - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug_Obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Debug_Obj/3eExplorer.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /profile

!ELSEIF  "$(CFG)" == "3eExplorer - Win32 Release Static"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "3eExplorer___Win32_Release_Static"
# PROP BASE Intermediate_Dir "3eExplorer___Win32_Release_Static"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Static"
# PROP Intermediate_Dir "Release_Static_Obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /profile
# Begin Custom Build
OutDir=.\Release_Static
ProjDir=.
InputPath=.\Release_Static\3eExplorer.exe
SOURCE="$(InputPath)"

"$(OutDir)\3eExplorer.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\3eExplorer.txt" "$(OutDir)" /y 
	date /t >> "$(OutDir)\3eExplorer.txt" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "3eExplorer - Win32 Release"
# Name "3eExplorer - Win32 Debug"
# Name "3eExplorer - Win32 Release Static"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\3eExplorer.cpp
# End Source File
# Begin Source File

SOURCE=.\3eExplorer.rc
# End Source File
# Begin Source File

SOURCE=.\3eExplorerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\3eExplorerView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ContentView.cpp
# End Source File
# Begin Source File

SOURCE=.\DetailView.cpp
# End Source File
# Begin Source File

SOURCE=.\DiskAllocationView.cpp
# End Source File
# Begin Source File

SOURCE=.\DocumentStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\ExplorerFile.cpp
# End Source File
# Begin Source File

SOURCE=.\HdfHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\IDEDOS_Plus3DosPartition.cpp
# End Source File
# Begin Source File

SOURCE=.\IDEDOS_SystemPartition.cpp
# End Source File
# Begin Source File

SOURCE=.\IDEDOSPartitionDefinition.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Plus3DOS_DirectoryEntry.cpp
# End Source File
# Begin Source File

SOURCE=.\Plus3DOS_UserArea.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TreeObject.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\3eExplorer.h
# End Source File
# Begin Source File

SOURCE=.\3eExplorerDoc.h
# End Source File
# Begin Source File

SOURCE=.\3eExplorerView.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ContentView.h
# End Source File
# Begin Source File

SOURCE=.\DetailView.h
# End Source File
# Begin Source File

SOURCE=.\DiskAllocationView.h
# End Source File
# Begin Source File

SOURCE=.\DocumentStatus.h
# End Source File
# Begin Source File

SOURCE=.\ExplorerFile.h
# End Source File
# Begin Source File

SOURCE=.\HdfHeader.h
# End Source File
# Begin Source File

SOURCE=.\IDEDOS_Plus3DosPartition.h
# End Source File
# Begin Source File

SOURCE=.\IDEDOS_SystemPartition.h
# End Source File
# Begin Source File

SOURCE=.\IDEDOSPartitionDefinition.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\memdc.h
# End Source File
# Begin Source File

SOURCE=.\OptionsDialog.h
# End Source File
# Begin Source File

SOURCE=.\Plus3DOS_DirectoryEntry.h
# End Source File
# Begin Source File

SOURCE=.\Plus3DOS_UserArea.h
# End Source File
# Begin Source File

SOURCE=.\registry.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StatusView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TreeObject.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\3eExplorer.ico
# End Source File
# Begin Source File

SOURCE=.\res\3eExplorer.rc2
# End Source File
# Begin Source File

SOURCE=.\res\3eExplorerDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\app.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tree_ico.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tree_ico_mask.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\3eExplorer.txt
# End Source File
# Begin Source File

SOURCE=.\plus3dos.zsm
# End Source File
# Begin Source File

SOURCE=.\plus3dos_file_headers.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\tapfile_format.txt
# End Source File
# End Target
# End Project
