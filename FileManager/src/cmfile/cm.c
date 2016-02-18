/** $Id 2014-9-20 23:09:51 ldlan */
#include "cm.h"
#include "../fmdef.h"
#include "../error/error.h"
#include "../vector/vector.h"
#include "../config/options.h"
#include "../filesys/filesys.h"
#include "../filesys/logfile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *psrc_path = 0;
static char *pdes_path = 0;

/** 
 * check cm path before cm,
 * @return 0 if has invalid path, 1 if valid
 */

static int check_cm_path()
{
	int ind;

	if(opt.src_dir) psrc_path = opt.src_dir;
	else if(opt.home_dir) {  // use home dir for it
		//p_warn("cm src path is null, use home dir to cm");
		psrc_path = opt.home_dir;
	}
	else {
		p_error(0, "not hvae cm src path, \
please to set before use option - cm\n\n");
		return 0;
	}

	// del the '\' or '/'
	ind = strlen(psrc_path);
	if(psrc_path[ind-1] == '\\')
		psrc_path[ind-1] = '\0';

	if(opt.des_dir) 
		pdes_path = opt.des_dir;
	else if(opt.home_dir)
	{
		pdes_path = opt.home_dir;
	}
	else {
		p_error(0, "not hvae cm des path, \
please to set before use cm option\n\n");
		return 0;
	}
	ind = strlen(pdes_path);
	if(pdes_path[ind-1] == '\\')
		pdes_path[ind-1] = '\0';

	return 1;
}

/** 
 * clear and free all element in vector
 */
static void clear_cm_vec(vector_t* _vec)
{
	int i;

	if(!_vec) return;

	// not use pop_front 
	for(i=_vec->top; i<_vec->number+_vec->top; i++)
		free(_vec->vec[i%_vec->size]);

	clear_vector(_vec);
}

/** print commpare info
 */
static void print_cm_info(const char* cstr)
{
	write_log(cstr);
	printf("%s", cstr);
}

/** 
 * Compare files in diff mode 
 * @param src_file compelete info 
 * @param des_file_path complete path 
 * @returns 0 when last modified time is same
			>0 src file more  new
			<0 des file more  new
 */
static int cm_files_diff(vector_ele_type src_file, const char* des_file_path)
{
	time_t des_file_wtime = get_file_wtime(des_file_path);
	return (int)(src_file->wtime - des_file_wtime);
}

/** Main function to compare files/dirs and output info
 */
static void cm_run(vector_t* cm_dir_vec)
{
	char cm_dir[PATH_ALL_MAX],
		 common_dir[PATH_ALL_MAX];
	
	char log_msg[BUF_MAX];		// log to write
	cm_type* pcm_dir = 0;		// current cm dir

	/** files and dirs counter */
	int lose_all_file = 0, lose_all_dir  = 0;
	int diff_new_file = 0, diff_old_file =0;
	int lose_file_indir, lose_dir_indir;

	vector_t find_file_vec, find_dir_vec;

	init_vector(&find_file_vec);
	init_vector(&find_dir_vec);

	memset(common_dir, 0, sizeof common_dir);

	sprintf(log_msg,"cm\n\
src_dir=[%s]\n\
des_dir=[%s]\n\
-----------------------------\n", psrc_path, pdes_path);
	print_cm_info(log_msg);

	while(cm_dir_vec->number > 0) { /** cm loop until not hvae dir path */
		pcm_dir = pop_front(cm_dir_vec);  // curent cm dir name

		strcpy(common_dir, pcm_dir->name);

		sprintf(cm_dir, "%s\\%s", psrc_path, pcm_dir->name);  // get find dir

		lose_file_indir = lose_dir_indir = 0;

		find_dir_file(cm_dir, "*.*",		/** find source dir all files and dirs*/
			&find_dir_vec, &find_file_vec);

		/** Compare directorys */
		while(find_dir_vec.number > 0) {  
			destroy_vector_element(pcm_dir);

			pcm_dir = pop_front(&find_dir_vec);
			
			if(*common_dir)
				sprintf(cm_dir, "%s\\%s\\%s",pdes_path,common_dir, pcm_dir->name);  // current cm dir in destination dir
			else
				sprintf(cm_dir, "%s\\%s",pdes_path, pcm_dir->name);
			
			if(!file_dir_exists(cm_dir)) {  // dir not exist
				++lose_dir_indir;

				if(*common_dir)
					sprintf(cm_dir, "%s\\%s", common_dir, pcm_dir->name);  // get current common short name
				else
					sprintf(cm_dir, "%s", pcm_dir->name);
				
				if(opt.copy)  // copy when copy
				{
					copy_files_dirs(psrc_path, pdes_path, cm_dir);
					sprintf(log_msg, "lose    [dir]    .\\%s[copy]\n", cm_dir);
				}
				else
					sprintf(log_msg, "lose    [dir]    .\\%s\n", cm_dir);

				print_cm_info(log_msg);
			}
			else {
				if(*common_dir)
					sprintf(cm_dir, "%s\\%s", common_dir, pcm_dir->name);  // get current common short name
				else
					sprintf(cm_dir, "%s", pcm_dir->name);
				push_back(cm_dir_vec, create_vector_element(cm_dir, pcm_dir->wtime));    // save dir push vector
			}
		}

		// compare files
		while(find_file_vec.number > 0) {
			destroy_vector_element(pcm_dir);
			pcm_dir = pop_front(&find_file_vec);

			if(*common_dir)
				sprintf(cm_dir, "%s\\%s\\%s",pdes_path,common_dir,pcm_dir->name);  // current cm dir in destination dir
			else
				sprintf(cm_dir, "%s\\%s", pdes_path, pcm_dir->name);
			
			if(!file_dir_exists(cm_dir)) {  // file not exist
				++lose_file_indir;

				if(*common_dir)
					sprintf(cm_dir, "%s\\%s", common_dir, pcm_dir->name);  // get current short name
				else
					sprintf(cm_dir, "%s", pcm_dir->name);

				if(opt.copy)
				{
					copy_files_dirs(psrc_path, pdes_path, cm_dir);
					sprintf(log_msg, "lose             .\\%s[copy]\n", cm_dir);
				}
				else 
					sprintf(log_msg, "lose             .\\%s\n", cm_dir);

				print_cm_info(log_msg);
			}
			else if(opt.cm_diff)			 // exist but diff
			{
				int retid = cm_files_diff(pcm_dir, cm_dir);
				
				if(*common_dir)
					sprintf(cm_dir, "%s\\%s", common_dir, pcm_dir->name);  // get current short name
				else
					sprintf(cm_dir, "%s", pcm_dir->name);

				if(retid>0)
				{
					diff_new_file++;
					if(opt.copy)
					{
						copy_files_dirs(psrc_path, pdes_path, cm_dir);
						sprintf(log_msg, "diff             .\\%s[s>d...copy]\n", cm_dir);
					}
					else 
						sprintf(log_msg, "diff             .\\%s[s>d...new]\n", cm_dir);

					print_cm_info(log_msg);
				}
				else if(retid < 0)
				{
					diff_old_file++;
					sprintf(log_msg, "diff             .\\%s[s<d...]\n", cm_dir);
					print_cm_info(log_msg);
				}
			}
		}
		lose_all_file += lose_file_indir;
		lose_all_dir  += lose_dir_indir;
		destroy_vector_element(pcm_dir);  // destroy last  element
	}
	if(opt.cm_diff)
		sprintf(log_msg,"\nlose all files: %d, lose all dirs: %d, \
diff new files: %d, diff old files: %d\n\n", 
			lose_all_file, lose_all_dir, diff_new_file, diff_old_file);
	else
	{
		sprintf(log_msg,"\nlose all files: %d, lose all dirs: %d\n\n", 
			lose_all_file, lose_all_dir);
	}

	print_cm_info(log_msg);
	flush_log();  // fflush buf
	destroy_vector(&find_dir_vec);
	destroy_vector(&find_file_vec);
}

/**
 * cm file 
 */
void cmfile()
{
	vector_t cm_dir_vec;  /** cm dir to put common dir */

	init_vector(&cm_dir_vec);

	/** invalid src path or des path */
	if(!check_cm_path()) 
		return;

	/** add cm root to cm dir queue */
	push_back(&cm_dir_vec, create_vector_element("\0", 0));

	cm_run(&cm_dir_vec);
	
	destroy_vector(&cm_dir_vec);
}