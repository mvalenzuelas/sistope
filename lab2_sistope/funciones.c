#include "funciones.h"
#define read_d 0
#define write_d 1


/*
Entradas: 	
	entrada: 						Un fichero de texto en formato de lectura que contiene la información de entrada

	matrizImpactos: 				Una matriz vacia de enteros con 2 columnas y tantas filas como cantidad de particulas
									para almacenar la posicion de impacto de una particula y la cantidad de energia

	particualasPorProcesosEntero:	Valor entero de la division de la cantidad de particulas por la cantuidad
									de procesos solicitados

	particulasPorProceso:			Entero que representa cantidad de particulas que simular el proceso actual

	qValue:							Entero que representa el identidficador del prcoso que se esta ejecutan

Funcionalidad: 	
	Función que lee un fichero de texto de entrada que contenga la información de los impactos de las particulas,
	correspondiente para el proceso actual, teniendo en cuenta la cantidad de particulas que se deben leer en el
	proceso actual y cuantos se leyeron en el proceso anterior posicion, almacena dicha información en una matriz
	de enteros

Salidas: 
	Entrega por paso por referencia una matriz de enteros 'matriz de impactos' de orden canParticulas X 2. En cada fila se
	almacena la informacion de una particula, en su primera columna se indica la posicion de impacto de la particula y la 
	segunda columna indica la cantidad de energia producida por el impacto
*/

void leerArchivo(FILE* entrada, int** matrizImpactos,int particulasPorProcesoEntero,int particulasPorProceso, int qValue){
	int pos=0;
	int energy=0;
	char linea[60];
	for (int i = 0; i <= particulasPorProcesoEntero*qValue; ++i)
	{
		fgets(linea,60,entrada);
	}
	for(int f = 0; f < particulasPorProceso; f++){
		fscanf(entrada, "%d %d", &pos,&energy);
		matrizImpactos[f][0]=pos;
		matrizImpactos[f][1]=energy;
	}
	fclose(entrada);
}

/*
Entradas:
	arreglo: 			Arreglo de memoria del tipo de dato flotante que representa la cantidad de energia almacenada
						en cada posición del material

	cantCeldas: 		Entero que representa la cantidad de posiciones o celdas que tiene el material
	
	MIN_ENERGY:			Entero que representa la cantidad de energia minima que debe ejercer un particula al impactar
						con el material para que esta sea absorvida por el

	posicionImpacto:	Entero que representa la posicion en la que impacta una particula

	energiaImpacto:		Entero que representa la cantidad de energia que genera una particula al impactar con el material

Funcionalidad:
	Funcion que permite calcular y almacenar en 'arreglo' la cantidad de energia absorvida por el material al ser impactado
	por una particula en una determinada posicion y con una determinada energia

Salidas:
	Entrega por paso por referencia un arreglo de memoria de flotantes que representa y almacena por posicion la energia absorvida
	por un material al ser impactado por una particula

*/
void calcularEnergia(float* arreglo, int cantCeldas, float MIN_ENERGY, int posicionImpacto, int energiaImpacto){
	for (int i = 0; i < cantCeldas; i++){
		float calculoEnergia = arreglo[i] + ((1000 * energiaImpacto)/(cantCeldas * sqrt(fabs(posicionImpacto-i) + 1)));
		if (calculoEnergia >= MIN_ENERGY){
			arreglo[i] = calculoEnergia;
			
		}
	}	

}

/*
Entradas:
	cantParticulas:	Cantidad de particulas que golpean al material

	arreglo: 		Arreglo de memoria del tipo de dato flotante que representa la cantidad de energia almacenada
					en cada posición del material

	cantCeldas: 	Entero que representa la cantidad de posiciones o celdas que tiene el material

	matrizImpactos: Una matriz de enteros con 2 columnas y tantas filas como cantidad de particulas
					que almacena la posicion de impacto de una particula y la cantidad de energia

Funcionalidad:
	Funcion que permite simular los impactos realizados por una cantidad de particualas en un materiales de largo 
	determinado representado por un arreglo de memoria que almacena el total de energia absorvida total

Salidas:
	Entrega por paso por referencia un arreglo de memoria de flotantes que representa y almacena por posicion la energia absorvida
	por un material al ser impactado por todas las particulas indicadas en 'matrizImpactos'

*/

void simulacion(int cantParticulas, float* arreglo, int cantCeldas, int** matrizImpactos){
	float MIN_ENERGY = 0.001/cantCeldas;

	for (int i = 0; i < cantParticulas; i++){
		int posicionImpacto = matrizImpactos[i][0];
		int energiaImpacto = matrizImpactos[i][1];
		//printf("PI = %d EI = %d\n", posicionImpacto, energiaImpacto);
		calcularEnergia(arreglo, cantCeldas, MIN_ENERGY, posicionImpacto, energiaImpacto);
		
	}
	return;
}

/*
Entradas:
	arreglo: 	Arreglo de memoria del tipo de dato flotante que representa la cantidad de energia almacenada
				en cada posición del material tras aplicar la simulación

	cantCeldas:	Entero que representa la cantidad de posiciones o celdas que tiene el material
	
Funcionalidad: 
	Funcion que permite obtener la posición del material que más energia absorvio tras los impactos
Salidas:
	Entero 'imax' que representa la posicion del arreglo que más energia a absorvido
*/
int obtenerMaximo(float* arreglo, int cantCeldas){
	float max=0;
	int imax=-1;
	for (int i = 0; i < cantCeldas; i++){
		if (max<= arreglo[i]){
			max=arreglo[i];
			imax=i;
		}
	}
	return imax;
}

/*
Entradas:
	archivo:	Un fichero de texto en formato de escritura en donde se almacenara los resultados de la simulación

	arreglo:	Arreglo de memoria del tipo de dato flotante que representa la cantidad de energia almacenada
				en cada posición del material tras aplicar la simulación
	
	cantCeldas:	Entero que representa la cantidad de posiciones o celdas que tiene el material

Funcionalidad: 	
	Funcion que permite escribir en un archivo de texto los resultados de la simulación indicado en cada posicion
	la cantidad total de energia absorvida y ademas indicar que posicion que almacena más energia
				
Salidas:
		Como fichero de texto plano se entrega 'archivo' que contiene los resultados de la simulación
*/
void escribirArchivo(FILE* archivo, float* arreglo, int cantCeldas){
	int max = obtenerMaximo(arreglo,cantCeldas);
	fprintf(archivo,"%d  %f\n", max, arreglo[max]);
	for (int i = 0; i < cantCeldas; i++)
	{
		fprintf(archivo,"%d %f\n", i, arreglo[i]);
	}
	fclose(archivo);
}

/*
Entradas:
	resultados:		Matriz de flotantes en la cual se almacena el resultado del proceso que se esté ejecutando
	pid:			pid del proceso padre que se está ejecutando
	fd:				matriz de enteros la cual representa n tuberías (n = cantidad de procesos) la cual recibe la información desde el padre al hijo
	fd1:			matriz de enteros la cual representa n tuberías (n = cantidad de procesos) la cual envía la información al padre desde el hijo
	nValue:			valor entero el cual representa el número de celdas
	pValue:			valor entero el cual representa el número de procesos
	cValue:			valor entero el cual representa la cantidad de lineas del archivo de entrada
	oValue:			cadena de carácteres el cual representa el nombre del archivo de salida
	iValue			cadena de carácteres el cual representa el nombre del archivo de entrada

Funcionalidad: 	
	Función que permite crear n procesos hijos (n = valor de pValue), en el cual si el proceso es el padre, envía a través de 
	los pipes los argumentos necesarios para ejecutar la simulación. Cuando el proceso el cual se está ejecutando es uno de los hijos,
	se recibe a través de la tubería los argumentos enviados por el padre y los duplica en STDIN-FILENO, y luego trás la simulación recibe
	los resultados a través de STDOUT-FILENO, y cuando este termina almacena el resultado en una matriz.
				
Salidas:
		Salida por referencia de la matríz de flotantes de resultados.
*/
void simulacionMultiproceso(float** resultados, pid_t pid, int** fd, int** fd1, int nValue, int pValue, int cValue, int dValue, char* oValue, char* iValue){

	for (int i = 0; i < pValue; ++i)
	{
		pipe(fd[i]);
		pipe(fd1[i]);
		pid=fork();
		if (pid>0)
		{
			//sprintf(arregloid,"%d",i);
			close(fd[i][read_d]);
			write(fd[i][write_d],&nValue,4);
			write(fd[i][write_d],&pValue,4);
			write(fd[i][write_d],&cValue,4);
			write(fd[i][write_d],&i,4);
			write(fd[i][write_d],iValue,sizeof(iValue)*2);
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

			//Se entregan los parametros al programa bomb por el descriptor STDIN_FILENO
			close(fd[i][write_d]);
			dup2(fd[i][read_d],STDIN_FILENO);
			close(fd[i][read_d]);
			//Se obtiene los resultados de la simulación
			close(fd1[i][read_d]);
			dup2(fd1[i][write_d],STDOUT_FILENO);
			close(fd1[i][write_d]);
			char* a[]={"bomb",NULL};
			execv("./bomb",a);

		}	
	}
}