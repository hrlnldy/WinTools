/* $ 2014-9-18 10:42:33 ldlan $ */

#include "error.h"
#include "../view/window.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void p_error(int err_no, const char *fmt, ...)
{
	va_list args;
	
	if(fmt == 0) return;

	va_start (args, fmt);

	/** change text color before print */
	set_text_color(error_color);

	fprintf(stderr, "ERROR - ");

	if(err_no)
		fprintf(stderr, "[Error %d] %s: ", 
			err_no, strerror(err_no));

	vfprintf(stderr, fmt, args);

	if(fmt[strlen(fmt)-1] !='\n') 
		fprintf(stderr, "\n");

	restore_text_color();

	va_end (args);
}


void p_info(const char *fmt, ...)
{
	va_list args;

	if(fmt==0) return;
	
	va_start (args, fmt);

	set_text_color(info_color);	

	fprintf(stderr, "INFO - ");

	vfprintf(stderr, fmt, args);
	
	if(fmt[strlen(fmt)-1] !='\n') 
		fprintf(stderr, "\n");

	restore_text_color();

	va_end (args);
}

void p_warn(const char *fmt, ...)
{
	va_list args;
	
	if(fmt==0) return;
	
	va_start (args, fmt);

	set_text_color(warn_color);	
	
	fprintf(stderr, "WARING - ");
	
	vfprintf(stderr, fmt, args);
	
	if(fmt[strlen(fmt)-1] !='\n') 
		fprintf(stderr, "\n");

	restore_text_color();

	va_end (args);
}