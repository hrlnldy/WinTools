/* $Id 2014-9-28 10:09:21 ldlan $ */

#ifndef _MSTRING_H
#define _MSTRING_H
/** 
 * repace a char to other char
 */
char* str_chrrep(char* str, char from, char to);

/** 
 * continuation character appears once
 */
char* str_mulrep(char* str, char chr);

#endif /* _MSTRING_H */