#ifndef Funciones_h_
#define Funciones_h_
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

void leerArchivo(FILE* entrada, int** matrizImpactos,int cantParticulas,int particualasPorProceso, int qValue);
void calcularEnergia(float* arreglo, int cantCeldas, float MIN_ENERGY, int posicionImpacto, int energiaImpacto);
void simulacion(int cantParticulas, float* arreglo, int cantCeldas, int** matrizImpactos);
int obtenerMaximo(float* arreglo, int cantCeldas);
void escribirArchivo(FILE* archivo,float* arreglo, int cantCeldas);
extern void niceprint(int N, float *Energy, float max_energy);
#endif