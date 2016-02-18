#include "mystring.h"

#include <string.h>

/** 
 * repace a char to other char
 */
char* str_chrrep( char* str, char from, char to)
{
	int len = strlen(str), i;

	if(!str) return 0;
	
	for(i=0; i<len; ++i)
		if(str[i]==from) str[i]=to;

	return str;
}
/** 
 * continuation character appears once
 */
char* str_mulrep(char* str, char chr)
{
	int beg, end, i;
	int len = strlen(str);
	for(i=0; i<len; ++i) {
		if(str[i]==chr) end = beg = i;
		else continue;
		
		while(i<len) {
			if(str[++i]==chr) end++;
			else break;
		}
		if(beg<end) {
			strcpy(str+beg, str+end);
			len-=(end-beg);
			i=beg+1;
		}
	}

	return str;
}