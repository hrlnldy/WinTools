/* $ 2014-9-18 16:36:24 ldlan $ */

/* This file is part of fm.
 *
 * struct options for app to run,
 * here define function to set option value
 * with define commands.
 */

/** define command to set options value.
 * @note the string name of commands msut be
 *		 ascending order in here.
 */

#include "options.h"
#include "../fmdef.h"
#include "../error/error.h"
#include "../filesys/path.h"
#include "../cmdopt/cmdopt.h"
#include "../filesys/filesys.h"
#include "../filesys/logfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char exec_path[PATH_ALL_MAX];

/** here define command action type */
typedef int (*cmd_action)(const char *, const char *, void *);

/** CMD_DECLARE to declare a static command funciton
 *  and defintion after.
 */
#define CMD_DECLARE(func) static int func \
  (const char *, const char *, void *)

/** declare command function */

CMD_DECLARE(cmd_boolean);
CMD_DECLARE(cmd_string);

/** 
 * configuration for application to set
 * must be in order, it work in binary search.
 */
typedef struct _command{
	char *name;
	void *opt_val;
	cmd_action action;
}command;

command commands[] = {
	/**
	 * whe cmd_boolean :
	 * set "1" or "on" to on, set "0" or "off" to off
	 * when cmd_string
	 * set vlue for pointer
	 */
	{ "copy",		&opt.copy,				cmd_boolean},
	{ "des",		&opt.des_dir,			cmd_string},
	{ "diff",		&opt.cm_diff,			cmd_boolean},
	{ "exclude",	&opt.exclude,			cmd_string},
	{ "home",		&opt.home_dir,			cmd_string},
	{ "log",		&opt.logfile,			cmd_string},
	{ "src",		&opt.src_dir,			cmd_string},
	{ "strict",		&opt.cmd_strict,		cmd_boolean}
};

/** initiliate options begin, 
 * most default is 0, some is set 1 be on */
void init_exec_options()
{
#ifdef CMD_STRICT
	opt.cmd_strict = 1;
#else
	opt.cmd_strict = 0;
#endif
	opt.cm_diff = 0;
	opt.copy = 0;
	if(exec_path)
		opt.home_dir = _strdup(exec_path);
	else
		opt.home_dir = _strdup("C:\\");

	opt.logfile = 0;

	opt.src_dir = 0;	
	opt.des_dir = 0;

	opt.exclude = 0;
}

/** free res */
void clear_exec_opt()
{
	if(opt.home_dir) free(opt.home_dir);
	if(opt.logfile)  free(opt.logfile);
	if(opt.src_dir)  free(opt.src_dir);
	if(opt.des_dir)  free(opt.des_dir);
	if(opt.exclude)	 free(opt.exclude);
}

/**
 * return index of command if it is a valid comand,
 * or return -1. when not find
 *
 * @param index in commands
 *
 */
static int command_index (const char *command)
{
	int min = 0, max = ARRAY_SIZE (commands);
	if(!command) {
		p_error(0, "no command to set option value\n\n");
		return -1;
	}
	do
    {
		int i = (min + max) / 2;
		int cmp = _stricmp (command, commands[i].name);
		if (cmp == 0)
			return i;
		else if (cmp < 0)
			max = i - 1;
		else
			min = i + 1;
    }
	while (min <= max);
	return -1;
}

/** 
 * begin define command functions, 
 * cmd_boolean need to set options value
 * be off or on to run application.
 * @return 0 if set opt success
 */
static int cmd_boolean(const char *command, const char *value, 
					   void *option_val)
{
	int bool_value;
	
	if (!_stricmp (value, "on")
		|| (*value == '1' && !*(value + 1)))
		bool_value = 1;
	else if (!_stricmp (value, "off")
		|| (*value == '0' && !*(value + 1)))
		bool_value = 0;
	else
    {
		p_warn("%s: Please specify on/1 or off/0\n\n", command);
		return 1;
    }
	
	*(int *)option_val = bool_value;

	return 0;
}

/** 
 * retunr 0 if set exec_opt success
 */
static int cmd_string (const char *command, const char *value,
					   void *option_val)
{
	char **pstring = (char **)option_val;
	
	/** release memory before set new value */
	if(*pstring) free(*pstring);

	*pstring = _strdup (value);

	return 0;
}

/** 
 * get log file from command opt.
 * @param cid index of log commands
 */

int setlog(const char* command, const char *value)
{
	/** get directory path but log name */
	char path[STR_MAX], val[STR_MAX];
	char *p = 0;
	memset(path, 0, STR_MAX);
	memset(val, 0, STR_MAX);

	strcpy(path, value);
	
	transfer_path(path);

	if(!(p = strrchr(path, '\\'))) // test '\'
		p = strchr(path, ':');  // test ':'

	if(!p) {  /** only log name, write log in work dir */
		sprintf(val, "%s\\%s.log", exec_path, path);
	}
	/** get path of logf */
	else {

		if(*p == ':') strncpy(val, path, p-path+1);  // append ':'
		else if(*p == '\\') strncpy(val, path, p-path);  // del '\'

		if(!file_dir_exists(val))  { // path not exist.
			p_error(0, "set \"%s\" failed, path \"%s\" not exists\n\n",
				command, val);
			return -1;
		}

		// only path, but log name
		if(!(*++p)) {
			sprintf(val, "%s\\fmlog.log", val);
		}
		else {
			sprintf(val,"%s\\%s", val, p);
		}
	}
	set_log_handle(val);

	return setval(command, val);
}

/** 
 * check path whether exist
 * 
 * @return -1 if path not exist, 0 set exec opt success
 */
int setpath (const char *command, const char *value)
{
	char path[STR_MAX] = {0};
	int index;

	strcpy(path, value);
	// transfer path string to stdrand path.
	// note that if path is a file
	if(!translate_path(opt.home_dir, path, STR_MAX))
		return -1;

	if(file_dir_exists(path) == -1) {// path not exist.
		p_error(0, "set \"%s\" failed, path \"%s\" not exists\n\n",
			command, value);
		return -1;
	}
	else if(file_or_directory(path) == 1) {
		p_error(0, "set \"%s\" failed, path \"%s\" is a file \n\n",
			command, value);
		return -1;
	}
		
	index = strlen(path);

	if(path[index-1] == '\\')  // del '\\' end of path
		path[index-1] = '\0';

	index = strlen(path);
	if(path[index-1]==':') { 
		path[index] = '\\';
		path[index+1] = '\0';
	}
	
	return setval(command, path);	
}
/** Set options value 
 * @returns -1 error occurred.
 */
int setval(const char *command, const char *value)
{
	int ind;
	if(!command || !value) {
		p_error(0, "no command or value to set option value\n\n");
		return -1;
	}
	if((ind=command_index(command)) == -1) {
		p_warn("unkonw command\n\n");
		return -1;
	}
	return (*commands[ind].action)(command, value, commands[ind].opt_val);
}

/** 
 * get value by command
 * @returns 0 error occurred.
 */
const void* getval(const char* command)
{
	int ind = -1;
	if(!command) {
		p_error(0, "no command to set option value\n\n");
		return 0;
	}
	if((ind=command_index(command)) == -1) {
		p_warn("unkonw command\n\n");
		return 0;
	}
	return commands[ind].opt_val;
}
/** 
 * add exclude file to ignore list
 */
int appendval(const char* command, const char *value)
{
	char append[BUF_MAX] = {0};
	char **old_excludes = (char**)getval(command);
	if(old_excludes && *old_excludes)
		sprintf(append, "%s;%s", *old_excludes, value);
	else
		sprintf(append, "%s", value);

	return setval(command, append);
}
/** 
 * printf usage info, 
 * note that cmd and option format:
   fm -opt[opt][opt], also see:
   fm -opt[opt][arg], if option has an argument, also see:
 */
void print_usage ()
{
printf("\n\
Usage: fm [OPTION][argument]...\n\
input [fm -h / fm --help] get help\n\
\n");
}

void print_help_info()
{
	print_usage ();
	/* Had to split this in parts, so the #@@#%# Ultrix compiler and cpp
	   don't bitch.  Also, it makes translation much easier.  */
	printf("%s%s", ("\
\n\
option,  long options,  argument,  description\n"),("\
\n\
    -v,  --version      no         display the version of fm and exit.\n\
    -h,  --help         no         print this help.\n\
    -c,  --cm           no         before compare two file different, set\n\
                                   -src option to set source directory and\n\
                                   -des option to set destinition.\n\
    -p,  --path         no         print path of dir, same as home, src dir, \n\
                                   des dir...\n\
    -s,  --src          yes        set source directory, if does't set,\n\
                                   use home dir.\n\
    -d,  --des          yes        set destination directory, if does't set,\n\
                                   use home dir.\n\
    -o,  --home         yes        set home directory, if src/des dir does't\n\
                                   set, use home dir to that.\n\
    -l,  --log          yes        set log file, such as c:\\log, set log in\n\
                                   c:\\, and 'log' is a file, set log.log in\n\
                                   crruent dir.\n\
         --diff         no         compare diffrent files when compare.\n\
         --clean        no         clean screen.\n\
         --strict       yes        set command to strict mode in 'on/1' or\n\
                                   'off/0'\n\
         --exclude      yes        add file to ignore when files compare.\n\
         --copy         no         copy alls diff from src dir to des dir.\n\
\n"));	
}

void print_opt_path()
{
	if(opt.home_dir) printf("home_dir=%s\n", opt.home_dir);
	else printf("home_dir=(NULL)\n");
	
	if(opt.src_dir) printf("src_dir=%s\n", opt.src_dir);
	else if(opt.home_dir) printf("src_dir=(NULL)%s\n", opt.home_dir);
	else printf("src_dir=(NULL)\n");
	
	if(opt.des_dir) printf("des_dir=%s\n", opt.des_dir);
	else if(opt.home_dir) printf("des_dir=(NULL)%s\n", opt.home_dir);
	else printf("des=(NULL)\n");
	
	printf("\n");
}

/** 
 * print all options
 */
void print_options()
{
	int i = 0;
	for(; i<sizeof(commands) / sizeof(command); ++i)
	{
		if(cmd_string == commands[i].action)
			printf("%s : %s\n", commands[i].name, *(char**)commands[i].opt_val);
		else
		{
			printf("%s : %d\n", commands[i].name, *(int*)commands[i].opt_val);
		}
	}
}