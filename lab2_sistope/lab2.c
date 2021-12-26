#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char*  argv[])
{
	int nValue=0;
	int pValue=0;
	int cValue=0;
	char* oValue=NULL;
	char* iValue=NULL;
	int c;
	opterr=0;

	while ((c=getopt(argc,argv,"N:p:c:o:i"))!= -1){
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
				iValue=optarg;	
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


	pid_t pid=getpid();
	pid_t pidAnterior;
	pid_t pidPadre=getpid();
	int status;
	int id;

	int** fd=(int**)malloc(sizeof(int*)*pValue);
	for (int i = 0; i < pValue; ++i)
	{
		fd[i]=(int*)malloc(sizeof(int)*2);
	}

	for (int i = 0; i < pValue; ++i)
	{
		
		if (pid>0)
		{
			/*
			pipe(fd[i]);
			char arregloid[30];
			char nValueStr[30];
			char pValueStr[30];
			char cValueStr[30];
			sprintf(nValueStr,"%d",nValue);
			sprintf(cValueStr,"%d",cValue);
			sprintf(pValueStr,"%d",pValue);
			sprintf(arregloid,"%d",id);
			char* argv2[]={"simular","-N",nValueStr,"-p",pValueStr,"-c",cValueStr,"-q",arregloid,"-i",iValue,NULL};
			*/
			id=i;
			pid=fork();
			//close(fd[i][0]);
			//write(fd[i][1],argv2,sizeof(argv2));
			//close(fd[i][1]);
		}
	}
	
	if (pid)
	{
		waitpid(pid,NULL,0);
		printf("Este es el padre\n");
	}
	if (pid==-1)
	{
		printf("Error al crear al hijo numero\n" );
	}
	if (pid==0)
	{
		printf("Pid:%d,getpid:%d\n",pid,getpid());
		char arregloid[30];
		char nValueStr[30];
		char pValueStr[30];
		char cValueStr[30];
		sprintf(nValueStr,"%d",nValue);
		sprintf(cValueStr,"%d",cValue);
		sprintf(pValueStr,"%d",pValue);
		sprintf(arregloid,"%d",id);
		char* argv2[]={"simular","-N",nValueStr,"-p",pValueStr,"-c",cValueStr,"-q",arregloid,"-i",iValue,NULL};
		//char* arr[100];
		//close(fd[id][1]);
		//read(fd[id][0],arr,sizeof(arr));
		//close(fd[id][0]);
		execv("/home/maximiliano/Escritorio/semestre6/sistope/lab2_sistope/simular",argv2);
	}

	return 0;
}