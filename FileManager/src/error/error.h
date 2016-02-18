/* $ 2014-9-18 10:24:15 ldlan $ */

/* deal with error, and print info of app,
 * also print info to log if need. */

#ifndef _ERROR_H
#define _ERROR_H

#include <errno.h>

/** error num definition, err_no */

#define err_ok 0
#define err_errno 1

/* print app info, error and warning */

/**
 * print error info to stderr
 *
 * @param err_no errno, type of error
 * @param fmt format string to print
 */
void p_error(int err_no, const char *fmt, ...);

/** 
 * print info to stderr
 *
 * @param err_no errno, type of error
 * @param fmt format string to print
 */
void p_info(const char *fmt, ...);

/** 
 * print warning info to stderr
 *
 * @param err_no errno, type of error
 * @param fmt format string to print
 */
void p_warn(const char *fmt, ...);

#endif /* _ERROR_H */
