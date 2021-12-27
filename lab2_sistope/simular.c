#include "funciones.h"


int main()
{
	
	int nValue;
	int pValue;
	int cValue;
	int qValue;
	char iValue[30];
	read(STDIN_FILENO,&nValue,4);
	read(STDIN_FILENO,&pValue,4);
	read(STDIN_FILENO,&cValue,4);
	read(STDIN_FILENO,&qValue,4);
	read(STDIN_FILENO,iValue,sizeof(iValue));	
	

	//Leer el archivo de entrada indicado en el comando '-i'
	FILE* entrada=fopen(iValue,"r");
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

	for (int i = 0; i <nValue; ++i)
	{
		write(STDOUT_FILENO,&arreglo[i],sizeof(float));
	}
	free(matrizImpactos);
	free(arreglo);


}