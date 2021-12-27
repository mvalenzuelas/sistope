#include "funciones.h"
#define read_d 0
#define write_d 1

int main(int argc, char*  argv[])
{
	int nValue=0;
	int pValue=0;
	int cValue=0;
	int dValue=0;
	char oValue[30];
	char iValue[30];
	int c;
	opterr=0;
	while ((c=getopt(argc,argv,"N:p:c:i:o:D"))!= -1){
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
				strcpy(oValue,optarg);
				break;
			case 'i':
				strcpy(iValue,optarg);	
				break;
			case 'D':
				dValue=1;
				break;
			case '?':
				if (optopt=='o'){
					fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
				}
				else if (isprint (optopt)){
          			fprintf (stderr, "Opcion desconocida `-%c'.\n", optopt);
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

	float** resultados=(float**)malloc(sizeof(float*)*pValue);
	for (int k = 0; k < nValue; ++k)
	{
		resultados[k]=(float*)malloc(sizeof(float)*nValue);
	}

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


			//Esperar que el proceso hijo sea ejecutado
			waitpid(pid,NULL,0);
			float* resultadoProceso=(float*)malloc(sizeof(float)*nValue);
			close(fd1[i][write_d]);
			for (int j = 0; j < nValue; ++j)
			{
				read(fd1[i][read_d],&resultadoProceso[j],sizeof(float));
			}
			close(fd1[i][read_d]);
			for (int j = 0; j < nValue; ++j)
			{
				resultados[i][j]=resultadoProceso[j];
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
			//Se obtiene los resultados de la simulación
			close(fd1[i][read_d]);
			dup2(fd1[i][write_d],STDOUT_FILENO);
			close(fd1[i][write_d]);
			char* a[]={"simular",NULL};
			execv("./simular",a);

		}
		
	}

	if (pid>0)
	{
		FILE* salida=fopen(oValue,"w");
		float* arreglo=(float*)malloc(sizeof(float)*nValue);
		for (int i = 0; i < nValue; ++i)
		{
			arreglo[i]=0;
			for (int j = 0; j < pValue; ++j)
			{
				arreglo[i]=resultados[j][i]+arreglo[i];

			}
		}
		int max= obtenerMaximo(arreglo,nValue);
		escribirArchivo(salida,arreglo,nValue);
		if (dValue)
		{
			niceprint(nValue,arreglo,arreglo[max]);
		}
		free(arreglo);
		for (int i = 0; i < nValue; ++i)
		{
			free(fd[i])
			free(fd1[i])
			free(resultados[i])
		}
		free(fd);
		free(fd1);
		free(resultados);
		free(arreglo);


	}

	return 0;
}