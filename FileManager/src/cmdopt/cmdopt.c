/* $ 2014-9-18 20:47:07 ldlan $ */

#include "cmdopt.h"
#include "../config/options.h"
#include "../getopt/getopt.h"
#include <string.h>
#include <stdio.h>

int opt_cnt = 0;  /* calculate how many option be input */

void init_cmd_opt()
{
	/** set off print opt info by getopt */
	opterr = 1; 
}

void get_cmd_input()
{
	int i;  /** get char one by one */
	char c;
	optind = 0; /* every time begin to get option and
				 * call getoption function to explain
				 * option need to set optind be 0 */
	opt_cnt=0;
	
			/* get options from argv pass by main */

	printf(">");

	for(;;) {
		opt_ptr[opt_cnt] = opt_str[opt_cnt];
		for(i=0; c=getchar(); i++) {
			if(c==' ' || c=='\n') {  /* new line to get option, or end to input */
				opt_str[opt_cnt][i] = '\0';
				++opt_cnt;
				if(c==' ') break;  /** break to begin new line */
				
				if(!*opt_str[0]) --opt_cnt;  /** only get '\n' */

				return;  /** end to input */
			}

			opt_str[opt_cnt][i] = c;
		}
		/* note that comand and option format: command -option [argument] */
	}
}

/** get command and option by argc pass by main*/
void get_cmd_arg(int* argc, char** argv)
{
	for(opt_cnt = 0; opt_cnt < *argc; ++opt_cnt)
	{
		opt_ptr[opt_cnt] = opt_str[opt_cnt];

		if(opt_cnt == 0) // command
			strcpy(opt_str[opt_cnt], "fm");
		else
		{
			strcpy(opt_str[opt_cnt], argv[opt_cnt]);
		}
	}
	*argc = 1;
}