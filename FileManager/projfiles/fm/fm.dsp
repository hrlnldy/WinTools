# Microsoft Developer Studio Project File - Name="fm" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=fm - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "fm.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "fm.mak" CFG="fm - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fm - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "fm - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "fm - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"../../Bin/file-compare.exe"

!ELSEIF  "$(CFG)" == "fm - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"../../Bin/file-compare.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "fm - Win32 Release"
# Name "fm - Win32 Debug"
# Begin Group "res"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;h;rc"
# Begin Source File

SOURCE=..\..\src\res\fm.rc
# End Source File
# Begin Source File

SOURCE=..\..\src\res\icon.ico
# End Source File
# Begin Source File

SOURCE=..\..\src\res\resource.h
# End Source File
# End Group
# Begin Group "view"

# PROP Default_Filter "c;h;"
# Begin Source File

SOURCE=..\..\src\view\window.c
# End Source File
# Begin Source File

SOURCE=..\..\src\view\window.h
# End Source File
# End Group
# Begin Group "error"

# PROP Default_Filter "c;h;"
# Begin Source File

SOURCE=..\..\src\error\error.c
# End Source File
# Begin Source File

SOURCE=..\..\src\error\error.h
# End Source File
# End Group
# Begin Group "config"

# PROP Default_Filter "c;h;"
# Begin Source File

SOURCE=..\..\src\config\options.c
# End Source File
# Begin Source File

SOURCE=..\..\src\config\options.h
# End Source File
# Begin Source File

SOURCE=..\..\src\config\version.c
# End Source File
# Begin Source File

SOURCE=..\..\src\config\version.h
# End Source File
# End Group
# Begin Group "getopt"

# PROP Default_Filter "c;h;"
# Begin Source File

SOURCE=..\..\src\getopt\getopt.c
# End Source File
# Begin Source File

SOURCE=..\..\src\getopt\getopt.h
# End Source File
# End Group
# Begin Group "cmdopt"

# PROP Default_Filter "c;h"
# Begin Source File

SOURCE=..\..\src\cmdopt\cmdopt.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cmdopt\cmdopt.h
# End Source File
# End Group
# Begin Group "string"

# PROP Default_Filter "c;h;"
# Begin Source File

SOURCE=..\..\src\string\getstr.c
# End Source File
# Begin Source File

SOURCE=..\..\src\string\getstr.h
# End Source File
# Begin Source File

SOURCE=..\..\src\string\mystring.c
# End Source File
# Begin Source File

SOURCE=..\..\src\string\mystring.h
# End Source File
# End Group
# Begin Group "vector"

# PROP Default_Filter "c;h;"
# Begin Source File

SOURCE=..\..\src\vector\vector.c
# End Source File
# Begin Source File

SOURCE=..\..\src\vector\vector.h
# End Source File
# End Group
# Begin Group "cmfile"

# PROP Default_Filter "c;h;"
# Begin Source File

SOURCE=..\..\src\cmfile\cm.c
# End Source File
# Begin Source File

SOURCE=..\..\src\cmfile\cm.h
# End Source File
# End Group
# Begin Group "filesys"

# PROP Default_Filter "c;h;"
# Begin Source File

SOURCE=..\..\src\filesys\filesys.c
# End Source File
# Begin Source File

SOURCE=..\..\src\filesys\filesys.h
# End Source File
# Begin Source File

SOURCE=..\..\src\filesys\path.c
# End Source File
# Begin Source File

SOURCE=..\..\src\filesys\path.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\src\fm.c
# End Source File
# Begin Source File

SOURCE=..\..\src\fmdef.h
# End Source File
# Begin Source File

SOURCE=..\..\src\test.c
# End Source File
# End Target
# End Project
