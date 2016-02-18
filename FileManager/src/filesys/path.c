#include "path.h"
#include "../fmdef.h"
#include "../error/error.h"
#include "../string/mystring.h"
#include "../vector/stack.h"
#include "filesys.h"
#include <string.h>
#include <stdio.h>
#include <direct.h>

/** 
 * get standard path in windows
 */
void transfer_path(char* path)
{
	str_chrrep(path, '/', '\\');
	str_mulrep(path, '\\');
}

/** translate gived path to absolute path.
 */
char* translate_path(const char* ab_path,
				    char* trans_path, int path_len)
{
	char new_path[PATH_ALL_MAX];
	char *first, *next;  // pointer to new string
	char *pchr;  // pointer ot gived path
	
	int len;

	if(!ab_path || !trans_path)
		p_warn("param error in function: translate_path\n\n");

	transfer_path(trans_path);
	
	memset(new_path, 0, PATH_ALL_MAX);

	if(!(pchr=strchr(trans_path, '.'))) // pchr pointer to firs '.' of gived path
		return trans_path; 

	
	if(pchr-1 <= trans_path)
		strcpy(new_path, ab_path);  // use home dir
	else 
		strncpy(new_path, trans_path,  // from gived dir
				pchr-trans_path);
	
	len=strlen(new_path);

	if(new_path[len-1]=='\\') 
		new_path[len-1] = '0';

	first = strrchr(new_path, '\\');  // pointer to '\'
	next = new_path+len;  // pointer to end of string

	len = strlen(trans_path);

	for( ; (pchr<trans_path+len) && 
		   (next<new_path+PATH_ALL_MAX) ; ){
		if(*pchr == '.')
		{
			pchr++;
			if(*pchr == '.'){
				if(first==0) p_error(0, "path error in function: translate_path\n\n");
				*(next = first) = 0;

				first = strrchr(new_path, '\\');
				pchr++;
			}
		}
		*next++ = *pchr++;
	}

	*next = 0;
	
	// break because of non-memory
	if(pchr<trans_path+len) {
		p_warn("non-memory to continue in function: translate_path\n\n");
		return 0;
	}

	str_mulrep(new_path, '\\');
	if(strlen(new_path)>(unsigned int)path_len) {
		p_warn("non-memory to continue in function: translate_path\n\n");
		return 0;
	}
	
	strcpy(trans_path, new_path);

	return trans_path;
}

/** 
 * Normalizes the path
 */
char* normalized_path(char* path)
{
	char path_name[PATH_ALL_MAX] = {0};
	stack_t stack, revstack;  // subdir stack
	stack_ele_type e = (stack_ele_type)0;

	char* subdir_star = path, *subdir_end = 0;  // subdir ending ('\') of path

	// step 1 : replace '/' to '\'
	str_chrrep(path, '/', '\\');
	// step 2 : parse path and push stack
	stack = create_stack();
	
	while (subdir_end = strchr(subdir_star, '\\'))
	{
		memset(path_name, 0, PATH_ALL_MAX);
		strncpy(path_name, subdir_star, subdir_end-subdir_star);
		if(!strcmp(path_name, ".."))
		{
			destroy_stack_element(stack_pop(&stack));
		}
		else if(strcmp(path_name, "."))
			stack_push(&stack, create_stack_element(path_name));
		
		subdir_star = subdir_end+1;
	}
	// get compelete name
	memset(path_name, 0, PATH_ALL_MAX);
	revstack = create_stack();
	while (e = stack_pop(&stack))
		stack_push(&revstack, e);

	e = stack_pop(&revstack);
	sprintf(path_name, "%s", e);
	destroy_stack_element(e);

	while (e = stack_pop(&revstack))
	{
		sprintf(path_name, "%s\\%s", path_name, e);  // maybe will be faied.
		destroy_stack_element(e);
	}

	destroy_stack(&stack);
	destroy_stack(&revstack);
	sprintf(path, "%s\\%s", path_name, subdir_star);  // maybe will be faied.

	return path;
}

/**
 * whether it is absolute path 
 * @returns 0 not, -1, not path, other is a ab path
 */
int absoulute_path(char* path)
{
	if(!file_dir_exists(path))
		return -1;
	return (int)strchr(path, ':');
}