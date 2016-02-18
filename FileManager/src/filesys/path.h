/** $Id 2014-9-28 10:24:40 ldlan $ */

#ifndef _DO_PATH_H
#define _DO_PATH_H

/** 
 * get standard path in windows
 */
void transfer_path(char* path);

/** translate gived path to absolute path.
 */
char* translate_path(const char* ab_path, char* trans_path, int path_len);

/** 
 * Normalizes the path
 */
char* normalized_path(char* path);

/**
 * whether it is absolute path 
 * @returns 0 not, -1, not path, other is a ab path
 */
int absoulute_path(char* path);

#endif /* _DO_PATH_H */