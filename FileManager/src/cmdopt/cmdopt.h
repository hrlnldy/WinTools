/* $ 2014-9-18 20:45:29 ldlan $ */

/* option input or output
 */
#ifndef _OPT_APP_H
#define _OPT_APP_H

#ifndef STR_MAX
#define STR_MAX 512
#endif

#ifndef OPT_MAX
#define OPT_MAX 128
#endif

#define CMD_STRICT 1  /** set command stric will set 1 */

extern char opt_str[OPT_MAX][STR_MAX];

extern char *opt_ptr[OPT_MAX];  /** pointer to opt_str */

/** init getopt */
void init_cmd_opt();

/** print exec cmd and opt info */
void print_usage();

/** get command and option input */
void get_cmd_input();

/** get command and option by argc pass by main*/
void get_cmd_arg(int* argc, char** argv);

#endif /* _OPT_APP_H */