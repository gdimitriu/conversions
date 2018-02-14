/*
		Conversion program for compass to make a valid spi file for simulation with artisan library
		SYNOPSYS:	acompass name.spi lib.spi
		It replace the subcircuits who are part of library.
		It will be use with dummy cell (black box) in compass.
		ver 0.1 alpha
*/
#include<stdlib.h>
#include "common.h"

int main(int argc, char *argv[])
{
char subckt[7]=".SUBCKT";	/* what we search (the begining of block what we whant to modify) */
char temporar;		/* variable for read */
int counter;		/* counter for position */
char name[11];		/* name of cells */
char *readline;	/* one line read from file */
char testc;			/* caracter for testing */
int testi;			/* integer for test */
int i,j;				/* counters */
	if(argc<3)
	{
		printf("\n ERROR no file \n");
		printf("SYNOPSYS: accompass name.spi lib.spi\n");
		exit(-1);
	}
	/* open the streams for file who have list of cells and operate file */
	cell_list=(FILE *)fopen("cell_list","r");
	spice_file=(FILE *)fopen(argv[1],"rw");
	spice_lib=(FILE *)fopen(argv[2],"r");
	/* making  alocation */
	if((readline=(char *)calloc(256,sizeof(char)))==(char *)NULL)
	{
		perror("Error memory alocation");
		/* close the files */
		fclose(spice_file);
		fclose(cell_list);
		fclose(spice_lib);
		exit(-1);
	}
	/* get to the begining of files */
	rewind(cell_list);
	rewind(spice_file);
	rewind(spice_lib);
	while(feof(spice_file)==0)
	{
		fgets(readline,256,spice_file);
		if(strncmp(readline,subckt,7)==0)
		{
			i=8;
			for(j=0;j<11;j++) name[j]=0;
			j=0;
			while(readline[i]!=' ')
			{
				name[j]=readline[i];
				i++;
				j++;
			}
			if(csearch(name,cell_list)==0) printf("\n gasit\n");
		}
	}
	/* close the files */
	fclose(spice_file);
	fclose(cell_list);
	fclose(spice_lib);
	free(readline);
	exit(0);
}