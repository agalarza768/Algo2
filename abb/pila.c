#include "pila.h"
#include <stdlib.h>

#define CAPACIDAD_INICIAL 10
#define FACTOR_REDIM_DISM 0.5f
#define FACTOR_REDIM_AUM 2.0f
#define LIMITE_REDIMENSION 4


/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * ****************************************************************/

void pila_redimensionar(pila_t *pila,float factor_redimension){
	void **nuevos_datos =realloc( pila->datos , (size_t)(factor_redimension * (float)(pila->capacidad * sizeof(void*))));
	pila->datos=nuevos_datos;
	pila->capacidad = (size_t)(factor_redimension * (float)pila->capacidad);
}

pila_t *pila_crear(){
	pila_t *pila=malloc(sizeof(pila_t));
	if (pila==NULL){
		return NULL;
	}
	pila->datos=malloc(sizeof(void*)*CAPACIDAD_INICIAL);
	if (pila->datos==NULL){
		free(pila);
		return NULL;
	}
	pila->cantidad=0;
	pila->capacidad=CAPACIDAD_INICIAL;
	return pila;
}

void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
	return pila->cantidad==0;
}

bool pila_apilar(pila_t *pila, void *valor){
	if (pila->cantidad==pila->capacidad){
		pila_redimensionar(pila,FACTOR_REDIM_AUM);
	}
	pila->datos[pila->cantidad]=valor;
	pila->cantidad++;
	return true;
}

void *pila_ver_tope(const pila_t *pila){
	if (pila->cantidad==0){
		return NULL;
	}
	return pila->datos[pila->cantidad-1];
}

void *pila_desapilar(pila_t *pila){
	if (pila->cantidad==0){
		return NULL;
	}
	if (pila->capacidad>=pila->cantidad*LIMITE_REDIMENSION){
		pila_redimensionar(pila,FACTOR_REDIM_DISM);
	}
	pila->cantidad--;
	return pila->datos[pila->cantidad];
}
 
// ...
