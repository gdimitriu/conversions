/* Program pentru conversia din formatul acs in Origin */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#ifdef LINUX
	#include<unistd.h>
	#include<linux/limits.h>
	#include<sys/stat.h>
	#include<fcntl.h>
	#include<sys/types.h>
	char path[PATH_MAX]="../";
#else
	#include<io.h>
	#include<conio.h>
	#include<alloc.h>
	#include<process.h>
	#include<dir.h>
	char path[MAXPATH]="..\\";
#endif
char numevar[12];
FILE *in,*iesire;
double temp,temp1,negativ;
char cautare;
int t,i,k,r,test,flag;
int numarfisiere;
FILE **listaf,*debug;

typedef struct options
{
        double secundar;        //valoarea cu doua iteratii in urma
        double primar;          //valoarea cu o iteatie in urma
        double prima;           //prima valoare (valoarea negativa maxima)
        double ultima;          //ultima valoare (valoarea pozitiva maxima)
        int pozitie;            //pozitia zeroului in sir
        int contor;             //contor
        double zerouri;         //valoarea elementului zero
} options;
struct options *element;
void help(void)
{
        printf("\n Syntax: conversi in");
        printf("\n in=Input file");
}
//procedura de cautare a inceputului datelor
void caut_inceput(void)
{
recaut:
        test=0;
        while(t==0)
        {
                fscanf(in,"%c",&cautare);
                if(cautare=='#')
                {
                        t=1;
                }
                if(feof(in)) t=1;
        }
        k=1;r=0;
        while(!(r==1))
        {
                k++;
                r=caut(k);
        }
        if (test==0) goto recaut;
}

//procedura de cautare a varibilelor si initializarea fisierelor de iesire
int caut(int j)
{
	#ifdef LINUX
		for(i=0;i<12;i++)numevar[i]=0;
	#else
        	for(i=0;i<8;i++) numevar[i]=0;
        #endif
        i=0;
        t=0;
        while(t==0)
        {
                fscanf(in,"%c",&cautare);
                numevar[i]=cautare;
                if((cautare=='i') || (cautare=='I')) //pentru curent
                {
                        numevar[i]=cautare;
                        t=1;
                        i=1;
                        test++;
                }
                if((cautare=='v') || (cautare=='V')) //pentru tensiune
                {
                        numevar[i]=cautare;
                        t=1;
                        i=1;
                        test++;
                }
                if(cautare=='\n') return(1);

        }
        t=0;
        while(t==0)
        {
                if(i>=8) fscanf(in,"%c",&cautare);
                if(i<8)
                {
                        fscanf(in,"%c",&cautare);
                        numevar[i]=cautare;
                        i++;
                }
                if(cautare==')') //delimitator expresie
                {
                        numevar[i]='.';
                        numevar[i+1]='t';
                        numevar[i+2]='x';
                        numevar[i+3]='t';
                        if(j>2) listaf=realloc(listaf,sizeof(FILE));
                        listaf[j]=fopen(numevar,"wt");
                        t=1;
                }
        }

        return(0);
}

//procedura de scriere a numerelor pentru forma liniara
void procscriere(void)
{
        r=0;
        for(i=1;i<numarfisiere+1;i++)
        {
                element[i].primar=0;
                element[i].secundar=0;
                element[i].pozitie=0;
                element[i].contor=0;
                element[i].zerouri=1e-23;
                element[i].prima=0;
                element[i].ultima=0;
        }
        while(!(r==1))
        {
                for(i=1;i<numarfisiere+1;i++)
                {
                        fscanf(in,"%le",&temp);
                        if(element[i].contor==0)
                        {
                                element[i].primar=temp;
                                element[i].secundar=temp;
                                element[i].prima=temp;
                                element[i].zerouri=temp;
                        }
                        else
                        {
                                if(element[i].primar<0)
                                {
                                 if(temp>0)
                                 {
                                    if(element[i].primar<0 ) temp1=-element[i].primar;
                                    if(temp<temp1)
                                    {
                                        element[i].zerouri=temp;
                                        element[i].pozitie=element[i].contor;
                                    }
                                    else
                                    {
                                        element[i].zerouri=element[i].primar;
                                        element[i].pozitie=element[i].contor-1;
                                    }
                                 }
                                }
                        }
                        if(temp==0)
                        {
                                element[i].zerouri=1e-23;
                                element[i].pozitie=element[i].contor;
                        }
                        if(temp<0) negativ++;
                        element[i].contor++;
                        if(feof(in)) break;
                        element[i].ultima=temp;
                        element[i].secundar=element[i].primar;
                        element[i].primar=temp;
                        fprintf(listaf[i],"%le\n",temp);
                        fprintf(iesire,"%le ",temp);
                }
                fprintf(iesire,"\n");
                if(feof(in)) r=1;
        }
}

//functia logaritm modificata
double gabylog(double x)
{
        if(x==0) x=x;
        else
        {
        if(x<0)
        {
                if (x>-1)
                {
                        temp1=-x;
                        x=log10(temp1);
                }
                else
                if(x<-1)
                {
                        temp1=-x;
                        x=-log10(temp1);
                }
        }
        else x=log10(x);
        }
        return(x);
}

//procedura de scriere a numerelor pentru forma logaritmica

void procscrierelog(void)
{
        r=0;flag=0;
        for(i=1;i<numarfisiere+1;i++)
        {
                element[i].primar=0;
                element[i].secundar=0;
                element[i].contor=0;
        }
        while(!(r==1))
        {
                for(i=1;i<numarfisiere+1;i++)
                {
                        fscanf(in,"%le",&temp);
                        if(gabylog(element[i].zerouri)<0)
                        temp=gabylog(temp/pow(10,floor(gabylog(element[i].zerouri))));
                        if(gabylog(element[i].zerouri)>0)
                        temp=gabylog(temp/pow(10,ceil(gabylog(element[i].zerouri))));
                        element[i].contor++;
                        fprintf(listaf[i],"%le\n",temp);
                        fprintf(iesire,"%le ",temp);
                }
                if(feof(in)) r=1;
                fprintf(iesire,"\n");
        }
}

//Procedura de debug
void procdebug(void)
{
        for(i=1;i<numarfisiere+1;i++)
        {
                fprintf(debug,"zerou %le ",element[i].zerouri);
                fprintf(debug,"pozitie %d ",element[i].pozitie);
                fprintf(debug,"prima %le ",element[i].prima);
                fprintf(debug,"ultima %le ",element[i].ultima);
                fprintf(debug,"exponent %le\n",floor(gabylog(element[i].zerouri)));
        }
}

int main(int argc, char *argv[])
{
t=0;
listaf=calloc(2,sizeof(FILE));
        printf("\n Program de conversie ACS in origin");
        printf("\n @1999 Gabriel Dimitriu \n");
        if(argc<=1)
        {
                help();
                free(listaf);
                exit(2);
        }
        if(!(in=fopen(argv[1],"r")))
        {
                printf("\n Misssing %s",argv[1]);
                help();
                free(listaf);
                exit(1);
        }
        fseek(in,0,0);
        caut_inceput();
        iesire=fopen("complet.txt","wt");
        listaf[1]=fopen("sweep.txt","wt");
        numarfisiere=k-1;
        element=calloc(numarfisiere,sizeof(struct options));
        negativ=0;
        procscriere();
        fclose(in);
        fclose(iesire);
        for(i=1;i<numarfisiere+1;i++) fclose(listaf[i]);
        free(listaf);
        if(negativ)
        {
                printf("Aveti %e valori negative\n",negativ);
                printf("Doriti un calcul pentru o reprezentare logaritmica ?(D/N)");
                scanf("%c",&cautare);
                if((cautare=='D') || (cautare=='d'))
                {

			#ifdef LINUX
                        	mkdir("log",7666);
                        #else
                        	mkdir("log");
                        #endif
                        chdir("log");
                        for(i=0;i<12;i++)
                        {
                        	if((argv[1][i]=='L') && (argv[1][i+1]=='E')) goto jump;
                        	numevar[i]=argv[1][i];
                        }
jump:                   strcat(path,numevar);
                        in=fopen(path,"r");                        
                        fseek(in,0,0);
                        listaf=calloc(2,sizeof(FILE));
                        caut_inceput();
                        iesire=fopen("complet.txt","wt");
                        listaf[1]=fopen("sweep.txt","wt");
                        numarfisiere=k-1;
                        procscrierelog();
                        fclose(in);
                        fclose(iesire);
                        #ifdef LINUX
	                        for(i=2;i<numarfisiere+1;i++) fclose(listaf[i]);
	                #else
	                        for(i=1;i<numarfisiere+1;i++) fclose(listaf[i]);
	                #endif
                        free(listaf);
                        free(element);
                        chdir("..");
                }
        }
}
