#include "funciones.h"


int main(int argc, char **argv)
{
	clock_t start = clock();
	int nValue=0;
	char* iValue=NULL;
	char* oValue=NULL;
	int dValue=0;
	int c;
	opterr=0;

	while ((c=getopt(argc,argv,"N:i:o:D"))!= -1){
		switch(c){
			case 'N':
				sscanf(optarg,"%d",&nValue);
				break;
			case 'i':
				iValue=optarg;	
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

	//Leer el archivo de entrada indicado en el comando '-i'
	FILE* entrada=fopen(iValue,"r");
    if (entrada==NULL){
        perror("Error al abrir el archivo\n");
        return 0;
    }
	
	//Leer desde el archivo de entrada la cantidad de particulas indicadas en la primera linea del archivo
	int cantParticulas;
	fscanf(entrada,"%d",&cantParticulas);
	
	//Definir una matriz para almacenar los valor de energia de los impactos y su posicion
	int ** matrizImpactos = (int**)malloc(sizeof(int*)*cantParticulas);
	for(int f = 0; f < cantParticulas; f++){
		matrizImpactos[f] = (int*)malloc(sizeof(int)*2);
	}

	//Leer el archivo de entrada y llenar la matriz de impactos
	leerArchivo(entrada, matrizImpactos, cantParticulas);
	

	//Definir el material con sus posiciones y la energia almacenada en ella, todas en cero
	float* arreglo = (float*)malloc(sizeof(float)*nValue);
	for (int i = 0; i < nValue; i++){
		arreglo[i] = 0.0;
	}

	//Simular el calculo de los impactos en el material
	simulacion(cantParticulas, arreglo, nValue, matrizImpactos);

	FILE* salida=fopen(oValue,"w");
	escribirArchivo(salida,arreglo,nValue);

	clock_t end=clock();

	float total = (double)(end - start) / CLOCKS_PER_SEC;
	int max= obtenerMaximo(arreglo,nValue);
	printf("El maximo valor de energia es de: %f\n",arreglo[max]);
	printf("El tiempo de ejecución del programa es %f segundos\n",total);
	if (dValue==1)
	{
		
		niceprint(nValue,arreglo,arreglo[max]);
	}
	
	// Liberar memoria
	for (int i = 0; i < cantParticulas; i++){
		free(matrizImpactos[i]);
	}
	free(matrizImpactos);
	free(arreglo);
	
	
}