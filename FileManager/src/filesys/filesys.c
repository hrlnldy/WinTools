/** $Id 2014-8-27 00:10:50 ldlan $ */

#include "filesys.h"
#include "../fmdef.h"
#include "../config/options.h"
#include "../error/error.h"
#include "../vector/vector.h"
#include "../string/mystring.h"

#include <io.h>
#include <errno.h>
#include "stdio.h"
#include <string.h>
#include <sys/stat.h>
#include <direct.h>
#include <windows.h>

#define S_ISDIR(m) (((m) & (_S_IFMT)) == (_S_IFDIR))

/**
 * file or directory whether or not exists
 *
 * @return 0 if path not exist, otherwise exists
 */
int file_dir_exists(const char* path)
{
	int access = _access(path, 0);
	if(access == -1 && errno  != ENOENT)  // 文件被占用
	{
		return 1;
	}

	return (access >= 0);
}

/**
 * file or directory
 *
 *@return 0 if path is a directory, 1 otherwise (any kind of file);
 *        return -1 if an error occur
 */
int file_or_directory(const char* path)
{
	char mypath[BUF_MAX];
	struct stat buf;
	
	memset(mypath, 0, BUF_MAX);
	if((strlen(path) - 1) == (strrchr(path, '\\')-path))
	{
		strncpy(mypath, path, strlen(path)-1);
	}
	else
	{
		strncpy(mypath, path, strlen(path));
	}
	if((strlen(mypath) - 1) == (strrchr(mypath, ':')-mypath))
		strcat(mypath, "\\");
	if(stat(mypath, &buf) == -1) {
		return -1;
	}
	return S_ISDIR (buf.st_mode) ? 0 : 1;
}

/**
 * exclude subdir: '.' and '..'
 * @returns 0 when '.' or '..', otherwise 1 
 */
static int is_real_dir(const char* path)
{
	if(strcmp(path, ".") && strcmp(path, ".."))
		return 1;
	else
		return 0;
}


/** 
 * get extension of file.
 * @param path name or path for file
 * @returns index of string of file name, 0 hasn't a extension
 */
static const char* get_file_extension(const char* path)
{
	const char* p = strrchr(path, '.');
	if(p)
		return p+1;
	else
		return p;
}

/** 
 * @returns 1 if has ext. otherwise 0.
 */
static int has_file_extension(const char* path,const char* ext)
{
	if(get_file_extension(path))
		return (!_stricmp(get_file_extension(path), ext));
	else
		return 0;
}

/** 
 * get file name.
 * @param 
 */

/** exclude file in files ignore list 
 * @returns 1 exclude this file, otherwise 0
 */
static int is_exclude(const char* path)
{
	char ext[NAME_MAX];
	const char *p = 0;
	const char* excludes_start = *(char**)getval("exclude");
	while(excludes_start)
	{
		memset(ext, 0, NAME_MAX);
		p = strchr(excludes_start, ';');
		if(p)
		{
			strncpy(ext, excludes_start, p-excludes_start);
			excludes_start = p+1;
		}
		else
		{
			strcpy(ext, excludes_start);
			excludes_start = 0;
		}
		if(has_file_extension(path, ext) || !_stricmp(path, ext))
			return 1;
	}
	return 0;
}

/** 
 * get all directorys and files in path 
 * 
 */
int find_dir_file(const char* path,
				  const char* type,
				  vector_t *dirs_vec,
			      vector_t *files_vec)
{
	
	struct _finddata_t fdata; 
	long find;
	char find_fmt[PATH_ALL_MAX];
	char fullpath[PATH_ALL_MAX];

	if(!path && !files_vec && !dirs_vec)
		return 0;

	// must be dir
	if(file_or_directory(path) != 0) {
		p_error(0, "path: \"%s\" isn't a directory\n\n", path);
		return 0;
	}

	if(type)
		sprintf(find_fmt, "%s\\%s", path, type);
	else
		sprintf(find_fmt, "%s\\%*.*", path, type);

	if((find = _findfirst(find_fmt, &fdata))== -1l)
		return -1;
	else {
		if((fdata.attrib & _A_SUBDIR) &&  // dirs
			is_real_dir(fdata.name))
		{
			push_back(dirs_vec, create_vector_element(fdata.name, fdata.time_write));
		}
		else if(is_real_dir(fdata.name))  // files
			push_back(files_vec, create_vector_element(fdata.name, fdata.time_write));  // kinds of file

		while(!_findnext(find, &fdata)) {
			if(!is_real_dir(fdata.name) ) continue;
			sprintf(fullpath, "%s\\%s", path, fdata.name);
			
			if((fdata.attrib & _A_SUBDIR) &&	// dir
				!is_exclude(fdata.name) &&		// exclude the folder name
				!file_or_directory(fullpath)) { // link files
				push_back(dirs_vec, create_vector_element(fdata.name, fdata.time_write));
			}
			else if(!is_exclude(fullpath))		// // kinds of files, exclude extension
				push_back(files_vec, create_vector_element(fdata.name, fdata.time_write));  
		}
		_findclose(find);
	}	
	
	return 1;
}

/**
 * get the last write time of file 
 * @returns return 0 when file not is exist, other time of last write.
 */
time_t get_file_wtime(const char* path)
{
	struct stat buf;
	if(stat(path, &buf) != 0) {
		return 0;
	}
	return buf.st_mtime;
}


void copy_file(const char* src, const char* des)
{
	CopyFileA(src, des, FALSE);
}

void copy_dir(const char* src, const char* des)
{
	vector_t dirs, files;
	vector_ele_type target;
	int i=0;
	char srcpath[PATH_ALL_MAX] = {0};
	char despath[PATH_ALL_MAX] = {0};

	if(!file_dir_exists(src)) return;  // 源文件夹不存在
	if(!file_dir_exists(des))  // 不存在创建
	{
		_mkdir(des);
	}

	init_vector(&dirs);
	init_vector(&files);
	
	find_dir_file(src, "*.*", &dirs, &files);

	while (dirs.number>0)
	{
		target = pop_front(&dirs);

		sprintf(srcpath, "%s\\%s", src, target->name);
		sprintf(despath, "%s\\%s", des, target->name);

		copy_dir(srcpath, despath);

		destroy_vector_element(target);
	}
	while (files.number > 0)
	{
		target = pop_front(&files);

		sprintf(srcpath, "%s\\%s", src, target->name);
		sprintf(despath, "%s\\%s", des, target->name);

		copy_file(srcpath, despath);

		destroy_vector_element(target);
	}

	destroy_vector(&dirs);
	destroy_vector(&files);
}

/**
 * copy @param(name) form @param(src) to @param(des)
 */
void copy_files_dirs(const char* src, const char* des, char*name)
{
	char srcpath[PATH_ALL_MAX] = {0};
	char despath[PATH_ALL_MAX] = {0};
	sprintf(srcpath, "%s\\%s", src, name);
	sprintf(despath, "%s\\%s", des, name);

	if(!file_dir_exists(srcpath)) return;

	if(!file_or_directory(srcpath))   // dir
	{
		copy_dir(srcpath, despath);
	}
	else
	{
		copy_file(srcpath, despath);
	}
}