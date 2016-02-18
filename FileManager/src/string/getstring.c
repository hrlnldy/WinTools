/* $Id 2014-8-24 13:32:43 ldlan $ */
#include "getstring.h"
#include "../res/resource.h"
#include "../view/window.h"
#include "../error/error.h"
#include <windows.h>

extern HINSTANCE hinst;  /** use hanlde of instance defined in window.h */

const char* load_string(char* buf, unsigned int str_id, const int buf_size)
{
	if(buf == 0) return 0;

	if(hinst == NULL) {
		p_error(0, "hinst == NULL, load string id = %d failed.", str_id);
		return 0;
	}
	if(LoadString(hinst, str_id, buf, buf_size) == 0)
		return 0;

	return buf;
}
