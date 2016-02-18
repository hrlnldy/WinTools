/* $Id 2014-8-24 13:25:55 ldlan $ */
#ifndef _VERSION_INFO_H
#define _VERSION_INFO_H

/** must init version begin execute run */
void init_verinfo();

/** get version number in a string */
const char* get_version_str();

/** get exec info */
const char* get_exec_info();


#endif /* _VERSION_INFO_H */