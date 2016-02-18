/** $Id 2014-9-20 23:18:09 ldlan $ */
#ifndef _FILE_SYSTEM_H
#define _FILE_SYSTEM_H

#include <time.h>

typedef struct _vector vector_t;

/**
 * file or directory whether or not exists
 *
 * @return 0 if path not exist, otherwise exists
 */
int file_dir_exists(const char* path);

/**
 * file or directory
 *
 *@return 0 if path is a directory, 1 otherwise (any kind of file);
 *        return -1 if an error occur
 */
int file_or_directory(const char* path);

/** 
 * get all directorys and files in path 
 * exclude subdir: . and ..
 * 
 * @param path path to find, must be a dir
 * @param type is find type same as "*.filetype" "*.*"
 * @param dirs_vec find dir result
 */
int find_dir_file(const char* path, const char* type, 
				  vector_t *dirs_vec,
				  vector_t *files_vec);

/**
 * get the last write time of file 
 * @returns return 0 when file not is exist, other time of last write.
 */
time_t get_file_wtime(const char* path);

/**
 * copy @param(name) form @param(src) to @param(des)
 */
void copy_files_dirs(const char* src, const char* des, char*name);

#endif