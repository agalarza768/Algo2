#include "lista.h"
#include <stdlib.h>

typedef struct nodo {
    void* dato;
    struct nodo* prox;
} nodo_t;

struct lista {
    nodo_t *prim;
    nodo_t *ult;
    size_t largo;
};

struct lista_iter {
    nodo_t *actual;
    nodo_t *ant;
    lista_t* lista;
};


//PRIMITIVA DEL NODO

nodo_t* nodo_crear(void* valor, nodo_t* prox) {
    nodo_t* nodo = malloc(sizeof(nodo_t));

    if (nodo == NULL) {
        return NULL;
    }

    nodo->dato = valor;
    nodo->prox = prox;
    return nodo;
}

//PRIMITIVAS DE LA LISTA

lista_t *lista_crear(void) {
    lista_t* lista = malloc(sizeof(lista_t));

    if (lista == NULL) {
        return NULL;
    }
    lista->prim = NULL;
    lista->ult = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista) {
    return lista->largo == 0;
}

bool lista_insertar_primero(lista_t *lista, void *dato) {
    nodo_t* nuevo_nodo = nodo_crear(dato, lista->prim);

    if (nuevo_nodo == NULL) {
        return false;
    }

    if (lista->prim == NULL) {
        lista->ult = nuevo_nodo;
    }
    lista->prim = nuevo_nodo;
    
    lista->largo++;

    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
    nodo_t* nuevo_nodo = nodo_crear(dato, NULL);

    if (nuevo_nodo == NULL) {
        return false;
    }

    if (lista->prim == NULL) {
        lista->prim = nuevo_nodo;
    } else {
        lista->ult->prox = nuevo_nodo;
    }
    lista->ult = nuevo_nodo;

    lista->largo++;

    return true;
}

void *lista_borrar_primero(lista_t *lista) {
    if (lista->prim == NULL) {
        return NULL;
    }
    nodo_t* nodo_a_borrar = lista->prim;
    void* dato_a_devolver = nodo_a_borrar->dato;
    lista->prim = lista->prim->prox;

    if (lista->prim == NULL) {
        lista->ult = NULL;
    }

    free(nodo_a_borrar);

    lista->largo--;

    return dato_a_devolver;
}

void *lista_ver_primero(const lista_t *lista) {
    if (lista->prim == NULL) {
        return NULL;
    }
    return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista) {
    if (lista->ult == NULL) {
        return NULL;
    }
    return lista->ult->dato;
}

size_t lista_largo(const lista_t *lista) {
    return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)) {
    while (lista->prim != NULL) {
		void* dato = lista_borrar_primero(lista);
		if (destruir_dato != NULL) {
			destruir_dato(dato);
		}
	}
    free(lista);
}

// PRIMITIVAS DEL ITERADOR INTERNO

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
    nodo_t* actual = lista->prim;
    while (actual != NULL) {
        if (visitar != NULL) {
			if(!visitar(actual->dato, extra)) {
                return;
            }
		}
        actual = actual->prox;
    }
}


// PRIMITIVAS DEL ITERADOR EXTERNO

lista_iter_t *lista_iter_crear(lista_t *lista) {
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));

    if (iter == NULL) {
        return NULL;
    }
    iter->actual = lista->prim;
    iter->ant = NULL;
    iter->lista = lista;
    return iter;
}


bool lista_iter_avanzar(lista_iter_t *iter) {
    if (iter->actual != NULL) {
        iter->ant = iter->actual;
        iter->actual = iter->actual->prox;
        return true;
    }
    return false;
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
    if (iter->actual == NULL) {
        return NULL;
    }
    return iter->actual->dato;
}


bool lista_iter_al_final(const lista_iter_t *iter) {
    if (iter->actual == NULL) {
        return true;
    }
    return false;
}


void lista_iter_destruir(lista_iter_t *iter) {
    free(iter);
}


bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
    nodo_t* nuevo_nodo = nodo_crear(dato, iter->actual);

    if (nuevo_nodo == NULL) {
        return false;
    }

	if (iter->ant == NULL) {
		iter->lista->prim = nuevo_nodo;
    } else { 
        iter->ant->prox = nuevo_nodo;
    }
    
    if (lista_esta_vacia(iter->lista) || lista_iter_al_final(iter)) {
		iter->lista->ult = nuevo_nodo;
	}
	iter->actual = nuevo_nodo;
	
	iter->lista->largo++;

	return true;
}


void *lista_iter_borrar(lista_iter_t *iter) {
    if (lista_iter_al_final(iter)) {
        return NULL;
    }

    nodo_t* nodo_a_borrar = iter->actual;
    void* dato_a_devolver = nodo_a_borrar->dato;
    
    iter->actual = iter->actual->prox;

    if (iter->ant == NULL) {
        iter->lista->prim = iter->actual;
        if(iter->actual == NULL) {
            iter->lista->ult = NULL;
        }
    } else {
        iter->ant->prox = iter->actual;
        if(iter->actual == NULL) {
            iter->lista->ult = iter->ant;
        }
    }
    free(nodo_a_borrar);

    iter->lista->largo--;

    return dato_a_devolver;
}

