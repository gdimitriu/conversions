/*
	Functions for operating files and strings
	ver 0.1 alpha
*/
#include"common.h"
/*
	Function to get at begining of next line in read mode
*/
int begline(FILE *file)
{
	while(fgetc(file)!='\n');
	return 0;
}

/*
	Function who search for name of cell in declaration
*/
int csearch(char *target,FILE *patern)
{

}