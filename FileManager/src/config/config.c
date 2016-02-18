/* $ 2015-11-6 18:15:25 ldlan $ */

#include "config.h"
#include "options.h"
#include "../fmdef.h"
#include <stdio.h>
#include <string.h>

/** init */

void set_options(const char* command, const char* value)
{
	if(!strcmp(command, "src") || !strcmp(command, "des"))
	{
		setpath(command, value);
	}
	else if(!strcmp(command, "log"))
	{
		setlog("log", value);
	}
	else if(!strcmp(command, "exclude"))
	{
		setval("exclude", value);
	}
	else if(!strcmp(command, "diff"))
	{
		setval("diff", "on");
	}
	else if(!strcmp(command, "copy"))
	{
		setval("copy", "on");
	}
}

void init_fm_config()
{
	FILE* config_handle = fopen("fm.config", "r");
	if(config_handle)
	{
		char pair_lef[BUF_MAX]={0}, pair_right[BUF_MAX]={0};
		char* pl = pair_lef, *pr = pair_right;
 		int read_l = 1, read_r = 0;
		while (!feof(config_handle))
		{
			char c = fgetc(config_handle);
			switch (c)
			{
			case '=':  // left value change to right value
			{
				read_l = 0;
				read_r = 1;
			}
			break;
			case  '\n':  // reset
			{
				read_l = 1;
				read_r = 0;
				pl = pair_lef, pr = pair_right;
				set_options(pair_lef, pair_right);
				memset(pair_lef, 0, BUF_MAX);
				memset(pair_right, 0, BUF_MAX);
			}
			break;
			case EOF:
				set_options(pair_lef, pair_right);  // set last pair value
				break;
			default:
			{
				if(c!= '=' && read_l) *pl++ = c;
				else if(c!= '=' && read_r) *pr++ = c;
			}
			break;
			}
		}
		
		fclose(config_handle);
	}
}