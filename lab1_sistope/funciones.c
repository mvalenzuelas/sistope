#include "funciones.h"
/*
Entradas: 	
	entrada: 		Un fichero de texto en formato de lectura que contiene la información de entrada

	matrizImpactos: Una matriz vacia de enteros con 2 columnas y tantas filas como cantidad de particulas
					para almacenar la posicion de impacto de una particula y la cantidad de energia

	cantParticulas:	Cantidad de particulas que golpean al material

Funcionalidad: 	
	Función que lee un fichero de texto de entrada que contenga la información de los impactos de las particulas,
	posicion y cantidad de energia aplicada, y almacena dicha información en una matriz de enteros

Salidas: 
	Entrega por paso por referencia una matriz de enteros 'matriz de impactos' de orden canParticulas X 2. En cada fila se
	almacena la informacion de una particula, en su primera columna se indica la posicion de impacto de la particula y la 
	segunda columna indica la cantidad de energia producida por el impacto
*/
void leerArchivo(FILE* entrada, int** matrizImpactos, int cantParticulas){
	int elemento;
	for(int f = 0; f < cantParticulas; f++){
		for(int c = 0; c < 2; c++){
			fscanf(entrada, "%d", &elemento);
			matrizImpactos[f][c] = elemento;
		}
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
	fprintf(archivo,"%d = %f\n", max, arreglo[max]);
	for (int i = 0; i < cantCeldas; i++)
	{
		fprintf(archivo,"%d = %f\n", i, arreglo[i]);
	}
	fclose(archivo);
}

