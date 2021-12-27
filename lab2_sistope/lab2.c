#include "funciones.h"
#define read_d 0
#define write_d 1

int main(int argc, char*  argv[])
{
	
	int nValue=0;
	int pValue=0;
	int cValue=0;
	int dValue=0;
	char* oValue=NULL;
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
			case 'i':
				strcpy(iValue,optarg);	
				break;
			case 'o':
				oValue=optarg;
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

	// Se lee el archivo de entrada
	FILE* entrada=fopen(iValue,"r");
	if (entrada==NULL)
	{
		perror("El archivo de entrada no existe");
		return 0;
	}
	fclose(entrada);
	
	// Se obtiene el pid del proceso en ejecución
	pid_t pid=getpid();


	// Se crean las tuberías, representadas en una matríz con pValue filas
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

	// Se crea la matriz en donde se almacenarán los resultados
	float** resultados=(float**)malloc(sizeof(float*)*pValue);
	for (int k = 0; k < pValue; ++k)
	{
		resultados[k]=(float*)malloc(sizeof(float)*nValue);
	}

	// Se ejecuta la simulación multiproceso
	simulacionMultiproceso(resultados, pid, fd, fd1, nValue, pValue, cValue, dValue, oValue, iValue);

	// Si el pid actual es el padre, se escriben los resultados
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
		

		// Se libera la memoria
		free(arreglo);

		for (int i = 0; i < pValue; ++i)
		{
			free(fd[i]);
			free(fd1[i]);
			free(resultados[i]);
		}
		free(fd);
		free(fd1);
		free(resultados);
	}

	return 0;
}