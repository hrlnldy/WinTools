/* $ 2014-9-18 16:24:06 ldlan $ */

/* This file is part of fm.
 *
 * options for app to run.
 */
#ifndef _OPTIONS_H
#define _OPTIONS_H

struct options
{
	int cmd_strict;  /** command is strict or not strict */
	int cm_diff;	 /** compare diffrent files when compare
					   * set 1 be true, set 0 be false 
					   */
	int copy;		 /** copy when cm */
	/** 
	 * note that is pointer to heap memory, 
	 * when to set new value, or end to execute, 
	 * it is good practice always to release this memory
	 * by free
	 */

	char* home_dir;  /** home diretory */
	char* logfile;   /** log file name to save log */

	char* src_dir;   /** source diretory to compare file */
	char* des_dir;   /** destinition dir to compare file */

	char* exclude;	 /** list of exclude file extentsion */
};

extern struct options opt;

/** 
 * initiliate options begin, 
 * most default is 0, some is set 1 be on 
 */
void init_exec_options();

/** print help info */
void print_help_info();

/** print fm path such as:
 * home, src, des ...
 */
void print_opt_path();

/** release memory */
void clear_exec_opt();

/** 
 * check path whether exist
 * 
 * @return -1 if path not exist, 0 set exec opt success
 */

int setpath (const char *command, const char *value);
/** 
 * get log file from command opt.
 * @param cid index of log commands
 */

int setlog(const char* command, const char *value);

/**
 * set value of options
 * 
 * @param command string name in command
 * @param value need to set in options
 */
int setval (const char *command, const char *value);

/** 
 * add exclude file to ignore list
 */
int appendval(const char* command, const char *value);

/** 
 * get value by command
 * @returns 0 error occurred.
 */
const void* getval(const char* command);

/** 
 * print all options
 */
void print_options();

#endif /* _OPTIONS_H */