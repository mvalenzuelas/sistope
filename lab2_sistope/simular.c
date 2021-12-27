#include "funciones.h"


int main()
{

	char* const* argv2;
	read(STDIN_FILENO,argv2,100);
	
	int nValue=0;
	int pValue=0;
	int cValue=0;
	int qValue=0;
	char* iValue=NULL;
	int c;
	opterr=0;
	while ((c=getopt(12,argv2,"N:p:c:q:i"))!= -1){
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
			case 'q':
				sscanf(optarg,"%d",&qValue);
				break;
			case 'i':
				iValue=optarg;	
				break;
			default:
				abort();
		}
	}
 
	//Leer el archivo de entrada indicado en el comando '-i'
	FILE* entrada=fopen("entrada.in","r");
    if (entrada==NULL){
        perror("Error al abrir el archivo\n");
        return 0;
    }

	//Leer desde el archivo de entrada la cantidad de particulas indicadas en la primera linea del archivo
	int cantParticulas;
	fscanf(entrada,"%d",&cantParticulas);
	
	int particulasPorProceso=cantParticulas/pValue;

	if (cantParticulas%pValue!=0 && qValue==pValue-1)
	{
		particulasPorProceso=particulasPorProceso+cantParticulas%pValue;
	}

	//Definir una matriz para almacenar los valor de energia de los impactos y su posicion
	int ** matrizImpactos = (int**)malloc(sizeof(int*)*particulasPorProceso);
	for(int f = 0; f < particulasPorProceso; f++){
		matrizImpactos[f] = (int*)malloc(sizeof(int)*2);
	}
	//Leer el archivo de entrada y llenar la matriz de impactos
	leerArchivo(entrada, matrizImpactos,(cantParticulas/pValue),particulasPorProceso,qValue);
	//Definir el material con sus posiciones y la energia almacenada en ella, todas en cero
	float* arreglo = (float*)malloc(sizeof(float)*nValue);
	for (int i = 0; i < nValue; i++){
		arreglo[i] = 0.0;
	}
	//Simular el calculo de los impactos en el material
	simulacion(particulasPorProceso, arreglo, nValue, matrizImpactos);


	//Liberar memoria
	for (int i = 0; i < particulasPorProceso; i++){
		free(matrizImpactos[i]);
	}
	free(matrizImpactos);
	free(arreglo);
	write(STDOUT_FILENO,"HOLA",5);
}