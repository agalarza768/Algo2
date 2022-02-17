#include "cola.h"

#include <stdlib.h>


typedef struct nodo {
    void* dato;
    struct nodo* prox;
} nodo_t;


struct cola {
    nodo_t *prim;
    nodo_t *ult;
};

//PRIMITIVA DEL NODO

nodo_t* nodo_crear_c(void* valor) {
    nodo_t* nodo = malloc(sizeof(nodo_t));

    if (nodo == NULL) {
        return NULL;
    }

    nodo->dato = valor;
    nodo->prox = NULL;
    return nodo;
}



//PRIMITIVAS DE LA COLA

cola_t *cola_crear(void) {
    return calloc(1, sizeof(cola_t));
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)) {
	while (cola->prim != NULL) {
		void* dato = cola_desencolar(cola);
		if (destruir_dato != NULL) {
			destruir_dato(dato);
		}
	}
    free(cola);
}

bool cola_esta_vacia(const cola_t *cola) {
    return cola->prim == NULL && cola->ult == NULL;
}

bool cola_encolar(cola_t *cola, void *valor) {
    nodo_t* nuevo_nodo = nodo_crear_c(valor);

    if (cola == NULL || nuevo_nodo == NULL) {
        return false;
    }

    if (cola->prim == NULL) {
        cola->prim = nuevo_nodo;
    } else {
        cola->ult->prox = nuevo_nodo;
    }
    cola->ult = nuevo_nodo;
    return true;
}

void *cola_ver_primero(const cola_t *cola) {
    if (cola->prim == NULL) {
        return NULL;
    }
    return cola->prim->dato;
}

void *cola_desencolar(cola_t *cola){
    if (cola->prim == NULL) {
        return NULL;
    }
    nodo_t* nodo_a_desencolar = cola->prim;
    void* dato_a_devolver = nodo_a_desencolar->dato;
    cola->prim = cola->prim->prox;

    if (cola->prim == NULL) {
        cola->ult = NULL;
    }

    free(nodo_a_desencolar);

    return dato_a_devolver;
}
