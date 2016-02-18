/** $Id 2015-11-4 13:35:53 ldlan $ */

#include "syscmd.h"
#include <windows.h>

/**
 * run some command in windows
 */
void system_command(const char* cmd)
{
	system(cmd);
}