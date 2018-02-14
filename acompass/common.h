/*
	Header for common declaration
	ver 0.1 alpha
*/

#ifndef _COMMON_H
#define _COMMON_H 1
#include <stdio.h>
#include <string.h>
FILE *cell_list;  /* the file who contains the name of cell */
FILE *spice_file; /* the file who are operate */
FILE *spice_lib;  /* the file for library */
/* function to get at beginning of next line in read mode */
int begline(FILE *file);
/* function who search for name of cell */
int csearch(char *target,FILE *patern);
#endif