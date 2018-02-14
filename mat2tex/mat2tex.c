#include<stdio.h>
FILE *fp1;
FILE *fp2;
float temporar;
int numar,i,t=0;

int main(int argc,char *argv[])
{
   if(argc>1)
   {
	 fflush(stdin);
  	 fp1=fopen(argv[1],"r+b");		//deschid fisierul mat
 	 fp2=fopen(argv[2],"w+b");		//deschid noul fisier
 	 fseek(fp1,0,0);
	 for (i=0;t==0;i++)
	 {	 
	 	fscanf(fp1,"%f",&temporar);     //citesc din fisierul mat
		t=feof(fp1);			//testez sfirsitul fisierului
	 	fprintf(fp2,"%.2f",temporar);	//scriu in fisierul nou
	 	fprintf(fp2,"&");		//scriu terminatorul de casuta
	 	fseek(fp1,1,1);			//avansez in fisierul mat
	 }
	 fseek(fp2,-1,1);
	 fprintf(fp2,"\\");
	 fprintf(fp2,"\\");
	 fclose(fp1);
	 fclose(fp2);
    }
    else
    {
    	printf("\nUsage: mat2tex fis.mat fis.tex\n");
    	printf("Is used to translate the date from matlab to tabular for latex\n");
    	printf("Is used only 2 unity over point.\n");
    }
}	 	