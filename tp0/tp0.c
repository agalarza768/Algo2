#include "tp0.h"

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {
	int aux = *x;
	*x = *y;
	*y = aux;
}


int maximo(int vector[], int n) {
    if (n == 0) {
		return -1;
	}
	
	int pos_max = 0;
	for (int i = 1; i < n; i++) {
		if (vector[i] > vector[pos_max]) {
			pos_max = i;
		}
	}
	return pos_max;
}


int comparar(int vector1[], int n1, int vector2[], int n2) {
	for (int i = 0; i < n1 && i < n2; i++) {
		if (vector1[i] < vector2[i]) {
			return -1;
		} else if (vector1[i] > vector2[i]) {
			return 1;
		}
	}
	
	if (n1 == n2) {
		return 0;
	}
	if (n1 < n2) {
		return -1;
	} else {
		return 1;
	}
}


void seleccion(int vector[], int n) {
	for (int i = n; i > 0; i--){
		int max = maximo(vector, i);
		int* pos_max = &vector[max];
		int* pos_final = &vector[i-1];
		swap(pos_max, pos_final);
	}
}
