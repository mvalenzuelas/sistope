#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#define read_d 0
#define write_d 1

int main(int argc, char*  argv[])
{
	int nValue=0;
	int pValue=0;
	int cValue=0;
	char* oValue=NULL;
	char iValue[30];
	int c;
	opterr=0;
	while ((c=getopt(argc,argv,"N:p:c:i:o"))!= -1){
		switch(c){
			case 'N':
				sscanf(optarg,"%d",&nValue);
				break;
			case 'p':
				sscanf(optarg,"%d",&pValue);
				break;
			case 'c':
				sscanf(optarg,"%d",&c);
				break;
			case 'o':
				oValue=optarg;
				break;
			case 'i':
				strcpy(iValue,optarg);	
				break;
			case '?':
				if (optopt=='o'){
					fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
				}
        		else{
          			fprintf (stderr,"Opcion con caracter desconocido `\\x%x'.\n",optopt);
        		}
				return 1;
			default:
				abort();
		}
	}

	char arregloid[30];
	char nValueStr[30];
	char pValueStr[30];
	char cValueStr[30];
	sprintf(nValueStr,"%d",nValue);
	sprintf(cValueStr,"%d",cValue);
	sprintf(pValueStr,"%d",pValue);

	pid_t pid=getpid();
	pid_t pidAnterior;
	int status;
	int id;

	int** fd=(int**)malloc(sizeof(int*)*pValue);
	for (int i = 0; i < pValue; ++i)
	{
		fd[i]=(int*)malloc(sizeof(int)*2);
	}

	int** fd1=(int**)malloc(sizeof(int*)*pValue);
	for (int i = 0; i < pValue; ++i)
	{
		fd1[i]=(int*)malloc(sizeof(int)*2);
	}

	for (int i = 0; i < pValue; ++i)
	{
		pipe(fd[i]);
		pipe(fd1[i]);
		pid=fork();
		if (pid>0)
		{
			sprintf(arregloid,"%d",i);
			close(fd[i][read_d]);
			write(fd[i][write_d],&nValue,4);
			write(fd[i][write_d],&pValue,4);
			write(fd[i][write_d],&cValue,4);
			write(fd[i][write_d],&i,4);
			write(fd[i][write_d],iValue,sizeof(iValue));
			close(fd[i][write_d]);
			waitpid(pid,NULL,0);
			float* resultadoProceso=(float*)malloc(sizeof(float)*nValue);
			close(fd1[i][write_d]);
			for (int j = 0; j < nValue; ++j)
			{
				read(fd1[i][read_d],&resultadoProceso[j],sizeof(resultadoProceso[j]));
			}
			close(fd1[i][read_d]);
			FILE* test=fopen("test.txt","w");
			for (int j = 0; j < nValue; ++j)
			{
				fprintf(test, "%f\n",resultadoProceso[j]);
			}
			
			
		}
		if (pid==-1)
		{
			printf("Error al crear al hijo numero\n" );
		}
		if (pid==0)
		{

			//Se entregan los parametros al programa simular por el descriptor STDIN_FILENO
			close(fd[i][write_d]);
			dup2(fd[i][read_d],STDIN_FILENO);
			close(fd[i][read_d]);
			//
			close(fd1[i][read_d]);
			dup2(fd1[i][write_d],STDOUT_FILENO);
			close(fd1[i][write_d]);
			char* a[]={"simular",NULL};
			execv("./simular",a);

		}
		
	}

	
	return 0;
}