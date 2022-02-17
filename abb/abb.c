#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "abb.h"
#include "pila.h"

typedef struct abb_nodo {
    struct abb_nodo *izq;
    struct abb_nodo *der;
    char *clave;
    void *dato;
} abb_nodo_t;

struct abb {
    abb_nodo_t *raiz;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
    size_t cant;
};

struct abb_iter{
	pila_t *pila;
};


// FUNCIONES AUXILIARES

abb_nodo_t *abb_nodo_crear(){
	abb_nodo_t *abb_nodo = malloc(sizeof(abb_nodo_t));
	abb_nodo->izq = NULL;
	abb_nodo->der = NULL;
	return abb_nodo;
}

abb_nodo_t *buscar_nodo(abb_nodo_t *raiz , const char *clave, abb_comparar_clave_t cmp, abb_nodo_t **padre){
	if (!raiz) return NULL;
	if (cmp(clave,raiz->clave) == 0) return raiz;
	if(padre) {
		*padre = raiz;
	}
	if (cmp(clave, raiz->clave) < 0) return buscar_nodo(raiz->izq, clave, cmp, padre);  
	else return buscar_nodo(raiz->der,clave,cmp,padre);
	return NULL;                                                                   
}

size_t cantidad_de_hijos(abb_nodo_t *nodo){
	if (nodo->izq && nodo->der) return 2;
	if(nodo->izq || nodo->der) return 1;
	return 0;
}

abb_nodo_t *buscar_reemplazante(abb_nodo_t *borrado){
	abb_nodo_t *actual = borrado->der;
	while(actual->izq) actual=actual->izq;
	return actual;
}

void iter_in_apilar(pila_t* pila, abb_nodo_t *nodo) {
	if (!nodo) return;
	pila_apilar(pila, nodo);
	iter_in_apilar(pila, nodo->izq);
}

void destruir_nodo(abb_nodo_t *abb_nodo, abb_destruir_dato_t destruir_dato){
	if(destruir_dato){
		destruir_dato(abb_nodo->dato);
	}
	free(abb_nodo->clave);
	free(abb_nodo);
}	


//PRIMITIVAS DEL ARBOL BINARIO DE BUSQUEDA

abb_t *abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t *abb = malloc(sizeof(abb_t));
	if (!abb) return NULL;
	abb->raiz = NULL;
	abb->cmp = cmp;
	abb->destruir_dato = destruir_dato;
	abb->cant = 0;
	return abb;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	abb_nodo_t *padre = NULL;
	abb_nodo_t *nodo = buscar_nodo(arbol->raiz, clave, arbol->cmp, &padre);
	if (!nodo) {
		char* copia_clave = strdup(clave);
		if (!copia_clave) return false;
		abb_nodo_t *nuevo_nodo = abb_nodo_crear();
		if (!nuevo_nodo) return false;
		nuevo_nodo->clave = copia_clave;
		nuevo_nodo->dato = dato;
		if (padre) {
			if(arbol->cmp(clave, padre->clave) < 0) padre->izq = nuevo_nodo;
			else padre->der = nuevo_nodo;
		}else {
			arbol->raiz = nuevo_nodo;
		}
		arbol->cant++;
	} else {
		if (arbol->destruir_dato) {
			arbol->destruir_dato(nodo->dato);
		}
		nodo->dato = dato;
	}
	return true;
}

void *abb_obtener(const abb_t *arbol, const char *clave) {
	abb_nodo_t* nodo = buscar_nodo(arbol->raiz, clave, arbol->cmp, NULL);
	if (!nodo) return NULL;
	return nodo->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave) {
	return buscar_nodo(arbol->raiz, clave, arbol->cmp, NULL) != NULL;
}

size_t abb_cantidad(abb_t *arbol) {
    return arbol->cant;
}

void _abb_destruir(abb_t *arbol, abb_nodo_t *nodo) {
	if (!nodo) {
		return;
	}
	_abb_destruir(arbol, nodo->izq);
	_abb_destruir(arbol, nodo->der);
	
	if (arbol->destruir_dato) {
		arbol->destruir_dato(nodo->dato);
	}
	free(nodo->clave);
	free(nodo);
	return;
}

void abb_destruir(abb_t *arbol) {
	if (!arbol->raiz){
		free(arbol);
		return;
	}
	_abb_destruir(arbol, arbol->raiz);
	free(arbol);
}

void *abb_borrar(abb_t *arbol, const char *clave){
	abb_nodo_t *padre = NULL;
	abb_nodo_t *nodo_a_borrar = buscar_nodo(arbol->raiz, clave, arbol->cmp, &padre);

	if(!nodo_a_borrar) return NULL;
	void *dato_borrado = nodo_a_borrar->dato;

	if(cantidad_de_hijos(nodo_a_borrar) < 2) {		
		abb_nodo_t *hijo = nodo_a_borrar->izq ? nodo_a_borrar->izq : nodo_a_borrar->der;
		abb_nodo_t *aux = nodo_a_borrar;
		if (padre) {
			if (arbol->cmp(clave, padre->clave) < 0) padre->izq = hijo;
			else padre->der = hijo;
		}else arbol->raiz = hijo;
		destruir_nodo(aux, arbol->destruir_dato);
		arbol->cant--;

	} else {
		abb_nodo_t *reemplazante = buscar_reemplazante(nodo_a_borrar);
		char *clave_reemplazante = strdup(reemplazante->clave);
		void *dato_reemplazante = reemplazante->dato;
		abb_borrar(arbol, clave_reemplazante);
		if (arbol->destruir_dato){
			arbol->destruir_dato(nodo_a_borrar->dato);
		}
		char *clave_aux = nodo_a_borrar->clave;
		nodo_a_borrar->clave = clave_reemplazante;
		nodo_a_borrar->dato = dato_reemplazante;
		free(clave_aux);
	}
	return dato_borrado;
}


// ITERADOR INTERNO DEL ABB

bool _abb_in_order(abb_nodo_t *nodo, bool visitar(const char *, void *, void *), void *extra) {
	if (!nodo) return true;
	
	if(!_abb_in_order(nodo->izq, visitar, extra)) return false;
	if(visitar) {
		if(!visitar(nodo->clave, nodo->dato, extra)) return false;
	}
	return _abb_in_order(nodo->der, visitar, extra);
}

void abb_in_order(abb_t *arbol,bool visitar(const char *, void *, void *),void *extra) {
	if (!arbol->raiz) return;
	_abb_in_order(arbol->raiz, visitar, extra);
}

// PRIMITIVAS DEL ITERADOR EXTERNO DEL ABB

abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
	abb_iter_t* iter = malloc(sizeof(abb_iter_t));
	if (!iter) return NULL;

	pila_t* pila = pila_crear();
	if (!pila) return NULL;

	iter_in_apilar(pila, arbol->raiz);

	iter->pila = pila;
	return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter) {
	abb_nodo_t *nodo_desapilado = pila_desapilar(iter->pila);
	if(!nodo_desapilado) return false; 
	iter_in_apilar(iter->pila, nodo_desapilado->der);
	return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter) {
	abb_nodo_t *tope = pila_ver_tope(iter->pila);
	if (!tope) return NULL;
	return tope->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter) {
	return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t *iter) {
	pila_destruir(iter->pila);
	free(iter);
}
