/** $Id 2015-11-4 15:33:32 ldlan $ */

#include "logfile.h"
#include <string.h>

/** handle of log file
 */
FILE* log_file_hander = 0;

/** init handle of long file when set long 
 */
void set_log_handle(const char* log_path)
{
	log_file_hander = fopen(log_path, "w+");
}
/** Write log for compare information 
 */
int write_log(const char* log_msg)
{
	if(log_file_hander)
		return (int)fwrite(log_msg, sizeof(char), strlen(log_msg), log_file_hander);
	return 0;
}

/** close handle when application exit
 */
void clear_log_handle()
{
	if(log_file_hander)
		fclose(log_file_hander);
	log_file_hander = 0;
}

/** Flush log file buf 
 */
void flush_log()
{
	fflush(log_file_hander);
}