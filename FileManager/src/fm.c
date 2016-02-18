/** $Id 2014-9-9 16:42:53 ldlan $ */

#include "fmdef.h"
#include "cmfile/cm.h"
#include "view/window.h"
#include "error/error.h"
#include "getopt/getopt.h"
#include "cmdopt/cmdopt.h"
#include "config/options.h"
#include "config/version.h"
#include <stdio.h>
#include <string.h>
#include "platform/syscmd.h"
#include "filesys/logfile.h"
#include "config/config.h"


/** declare of extern */
extern int opt_cnt;

/**
 * define options for application, control
 * some function be on or off
 */

struct options opt;

char opt_str[OPT_MAX][STR_MAX];

char *opt_ptr[OPT_MAX];

const char *exec_cmd = "fm";

/**
 * long options to pass
 *
 * long_options definition
 * {
 *   long_option,									// name
 *   argument: be no_argument or required_argument  // wheath has argument
 *   return value descritption,						// flage
 *   return value									// value to return
 *  }
 *
 * also see: short options "chvpd:s:l:"
 */
static struct option long_options[] =
{	/** not need an argument */
    { "help", no_argument, NULL, 'h' },
	{ "cm", no_argument, NULL, 'c' },
	{ "version", no_argument, NULL, 'v'	},
	{ "path", no_argument, NULL, 'p'},
	{ "clean", no_argument, NULL, '0'},
	{ "exit", no_argument, NULL, 'x'},
	{ "diff", no_argument, NULL, 'f'},
	{ "option", no_argument, NULL, 'z'},
	{ "copy", no_argument, NULL, 'y'},

	/** need an argument */
	{ "home", required_argument, NULL,'o' },
	{ "log", required_argument, NULL, 'l' },
    { "src", required_argument, NULL, 's' },
    { "des", required_argument, NULL, 'd' },
	{ "strict", required_argument, NULL, 'i'},
	{ "exclude", required_argument, NULL, 'e'},

    { 0, 0, 0, 0 }
};


/** Initialize application */
int initialize(int argc, char **argv)
{
	init_window(argc, argv);
	init_verinfo();
	init_exec_options();
	init_cmd_opt();
	init_fm_config();

	return 0;
}

/** clean work */
void clear()
{
	clear_window();
	clear_exec_opt();
	clear_log_handle();
}

int main(int argc, char **argv)
{
	int c;

	int opterr_cnt=0;

	/** Exit application */
	int exit = 0;

	initialize(argc, argv);

	printf("%s", get_exec_info());

	print_usage();


	while(1) {  /** if close window dirctor, must be deal 
				 * with close window event to free resource */
		opterr_cnt = 0;

		if(argc > 1)
			get_cmd_arg(&argc, argv);
		else
			get_cmd_input();

		if(opt_cnt == 0)
			continue;
		
		else if(opt_cnt == 1)  /** don't allow only cmd */
		{
			if(opt.cmd_strict &&  /** if cmd is strict, don't allow
								   *  other command*/
			   _stricmp(exec_cmd, *opt_str))
			{
			   p_error(0, "command \"%s\" is not recognized", *opt_str);
			}
			print_usage();
			continue;
		}
		else if(opt.cmd_strict && /** if cmd is strict, don't allow
								   *  other command, continue to get new opt
								   */
			    _stricmp(exec_cmd, *opt_str))
		{
			p_error(0, "command \"%s\" is not recognized", *opt_str);
			print_usage();
			continue;
		}

		while((c=getopt_long (opt_cnt, (char* const*)opt_ptr, "\
chvpd:s:l:o:", long_options, (int *)0)) != EOF) {
			switch (c) {
			case 'c':
				cmfile();
				break;
			case 'd':
				setpath("des", optarg);
				break;
			case 'h':
				print_help_info();
				break;
			case 'l':
				setlog("log", optarg);
				break;
			case 'o':
				setpath("home", optarg);
				break;
			case 'p':
				print_opt_path();
				break;
			case 's':
				setpath("src", optarg);
				break;
			case 'v':
				printf("\n%s %s\n\n", exec_cmd, 
					get_version_str());
				break;
			case '0':
				system_command("cls");
				print_usage();
				break;
			case 'x':
				exit = 1;
				break;
			case 'f':
				setval("diff", "on");
				break;
			case 'i':		// set command in strict mode 
				setpath("strict", optarg);
				break;
			case 'e':
				setval("exclude", optarg);
				break;
			case 'y':
				setval("copy", "on");
				break;
			case 'z':
				print_options();
				break;;
			case '?':
				if(!opterr) {
					p_warn("Unkonw option");
				}
				++opterr_cnt;  /** count error option */
				break;
			}
		}

		if(exit)
			break;

		if(opterr_cnt)  /** only output one time usage info */
			print_usage();
	}

	clear();
	return 0;
}