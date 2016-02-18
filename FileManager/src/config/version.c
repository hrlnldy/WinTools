/* $Id 2014-8-24 14:32:38 ldlan $ */

#include "version.h"

#include "../fmdef.h"
#include "../res/resource.h"
#include "../string/getstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

unsigned short major_version;   /* major version, minor version
                                 * to see windows resource in string table
								 */
unsigned short minor_version;

char str_exec_info[STR_MAX],
	 str_exec_ver[STR_MAX];

void init_verinfo()
{
	char major_v[STR_MAX],
		 minor_v[STR_MAX];

	char exec_name[STR_MAX],
		 exec_desc[STR_MAX],
		 exec_cyright[STR_MAX];
	
	load_string(major_v, STR_VERSION_MAJOR, STR_MAX);
	load_string(minor_v, STR_VERSION_MINOR, STR_MAX);
	
	major_version = (unsigned short)atoi(major_v);
	minor_version = (unsigned short)atoi(minor_v);

	load_string(exec_name, STR_EXE_NAME, STR_MAX);
	load_string(exec_desc, STR_EXEC_DESCRIPTION, STR_MAX);
	load_string(exec_cyright, STR_EXEC_COPYRIGHT, STR_MAX);

	sprintf(str_exec_ver,"%d.%d", major_version, minor_version);

	sprintf(str_exec_info, "%s %s %s\n\
%s\n", exec_name, str_exec_ver, exec_cyright, exec_desc);
}


/** get version in a unsigned short */
unsigned int get_version()
{
	return (major_version << 8 | minor_version);		
}

/**
 * get version string contain major version and minor version
 * example 1, 1, return 1.1;
 */

const char* get_version_str()
{
	return str_exec_ver;
}

const char *get_exec_info(void)
{
	return str_exec_info;
}
