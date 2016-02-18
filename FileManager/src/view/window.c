/* $Id 2014-9-9 13:32:06 ldlan $ */
/*
 * file for console window. 
 */

#include "window.h"
#include "../fmdef.h"
#include "../error/error.h"
/** get icon id */
#include "../res/resource.h"
#include "../config/version.h"
#include "../string/mystring.h"
#include "../filesys/path.h"

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <direct.h>

/** instance handle of exec */
HINSTANCE hinst = NULL;

/** handle of window */
HWND hwnd = NULL;

/** full path name of exec */
char exec_path[PATH_ALL_MAX];

/** current work directory */
char cur_work_dir[PATH_ALL_MAX];

/** exec name */
char exec_name[NAME_MAX];

typedef HWND (WINAPI *WINDPROC)(void);

/** function to get handle of window */
WINDPROC GetConsoleWindowHandle = NULL;

/** 
 * use to save console screen buffer info, 
 * when need to change attribute of text need
 * to save in csbiInfo
 */
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

/** 
 * initialize window, set window title and set 
 * icon of winodw.

 * @param argc counter of argument pass by main
 * @param argv arg pass by main
 */

void init_window(int argc, char **argv)
{
	HMODULE hkernel32 = NULL;
	HANDLE hstdout = INVALID_HANDLE_VALUE;
	char *p_app_name;

	/** 
	 * get and save window buffer attitube,
	 * in order to store text color.
	 * */
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hstdout == INVALID_HANDLE_VALUE) {
		p_warn("get standard output handle failed, \
			   change color failed");
		return;
	}
	if(!GetConsoleScreenBufferInfo(hstdout, &csbiInfo)) {
		p_warn("get console window buffer info failed, \
			   change color failed");
		return;
	}

	/** 
	 * GetConsoleWindowHandle need to load address of
	 * kernel32.dll 
	 */
	hkernel32 = GetModuleHandle("kernel32");
	
	GetConsoleWindowHandle = (WINDPROC)GetProcAddress(hkernel32, "GetConsoleWindow");
	
	if(GetConsoleWindowHandle == NULL) 
		p_error(0, "Error - can't load fuction: GetConsoleWindow");
	else
		hwnd = GetConsoleWindowHandle();   // handle of window
	if(hwnd == 0) 
		p_error(0, "Error - can't get handle of console window");

	strcpy(exec_path, argv[0]);  // get application path by arg pass by os
	if(absoulute_path(exec_path)<=0)
	{
		GetModuleFileName(NULL, exec_path, PATH_ALL_MAX);
	}
	/** get application name */
	normalized_path(exec_path);

	hinst = GetModuleHandle(0);   // instace of application
	if(hinst == 0)
		hinst = GetModuleHandle(exec_path);

	p_app_name = strrchr(exec_path, '\\');
	if(!p_app_name) strcpy(exec_name, "fm.exe");
	else {
		p_app_name++;
		strcpy(exec_name, p_app_name);

		exec_path[p_app_name-exec_path-1] = '\0';
	}

	/** change cwd */
	if(_stricmp(exec_path, _getcwd(cur_work_dir, PATH_ALL_MAX)))
	{
		_chdir(exec_path);
	}

	/** set console title */
	SetConsoleTitle(exec_name);

	 /** set window icon */
	SendMessage(hwnd, WM_SETICON, ICON_SMALL,(LPARAM)
		LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON)));
}

void set_text_color(unsigned short color)
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hstdout == INVALID_HANDLE_VALUE) {
		p_warn("get standard output handle failed, \
change color failed");
		return;
	}
	/**
	 * set cosole window text color
	 * background color also default(0) 
	 */
	if (!SetConsoleTextAttribute(hstdout, color)) {  // 
		p_warn("set console window color failed, \
change color failed");
		return;
	}
}

void restore_text_color()
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hstdout == INVALID_HANDLE_VALUE) {
	p_warn("get standard output handle failed, \
		change color failed");
	return;
	}
	
	if (!SetConsoleTextAttribute(hstdout, csbiInfo.wAttributes)) {
	p_warn("set console window color failed, \
		restore window color failed");
	return;
	}
}

void clear_window()
{
	restore_text_color();
}
