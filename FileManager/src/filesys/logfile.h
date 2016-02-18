/** $Id 2015-11-4 15:32:57 ldlan $ */
#ifndef _LOG_FILE_H
#define _LOG_FILE_H

#include <stdio.h>

/** handle of log file
 */
extern FILE* log_file_hander;

/** Write log for compare information 
 */
int write_log(const char* log_msg);

/** init handle of long file when set long 
 */
void set_log_handle(const char* log_path);

/** close handle when application exit
 */
void clear_log_handle();

/** Flush log file buf 
 */
void flush_log();

#endif