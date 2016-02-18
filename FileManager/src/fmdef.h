/* $ 2014-9-18 10:06:18 ldlan $ */

/* common definition of app
 */

#ifndef _FM_DEFINITION_H
#define _FM_DEFINITION_H

/** definition of path, full path */
//#ifndef PATH_ALL_MAX
//#define PATH_ALL_MAX 256
//#endif

#ifndef BUF_MAX
#define BUF_MAX 1024
#endif

#ifndef PATH_ALL_MAX
#define PATH_ALL_MAX 1024
#endif

#ifndef NAME_MAX
#define NAME_MAX 128
#endif

#ifndef STR_MAX
#define STR_MAX 512
#endif

#ifndef NULL 
#define NULL 0
#endif

#ifndef EOF
#define EOF     (-1)
#endif

/** 
 * calculate how manry elements array has
 * note that arg array must be array, but it isnot 
 * a pointer
 */
#define ARRAY_SIZE(array) (sizeof (array) / sizeof (*(array)))

#endif /* _FM_DEFINITION_H */
