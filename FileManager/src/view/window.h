/* $Id 2014-9-9 13:29:15 ldlan $ */

/* file for console window. */
#ifndef _WINDOW_H
#define _WINDOW_H

/** window color */
#define error_color 0x0C //0x04
#define warn_color  0x06
#define info_color  0x07

/** 
 * initialize window, set window title and set 
 * icon of winodw...
 * @param argc counter of argument pass by main
 * @param argv pass by main
 */

void init_window(int argc, char **argv);

/** 
 * change text color
 * 
 * @param color definition in window.h, also
 *		  see define and description in windows.h
 */
void set_text_color(unsigned short color);

/**
 * restore color of window
 */

void restore_text_color();

/**
 * release resouce
 */
void clear_window();

#endif