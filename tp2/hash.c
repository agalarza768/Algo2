#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#define CAPACIDAD_INICIAL 19
#define FACTOR_DE_CARGA 0.7
#define CONST_DE_REDIMENSION 2

typedef enum estado {
    VACIO,
    OCUPADO,
    BORRADO,
} estado_t;

typedef struct campo {
    char *clave;
    void *dato;
    estado_t estado;
} campo_t;

struct hash {
    campo_t *tabla;
    size_t capacidad;
    size_t cantidad;
    size_t cant_no_vacios;
    hash_destruir_dato_t destruir_dato;
};

struct hash_iter {
	const hash_t* hash;
	size_t posicion;
};

// FUNCIONES AUXILIARES

unsigned long funcion_hash(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
	}
    return hash;
}

campo_t* hash_inicializar_tabla(hash_t* hash, size_t capacidad) {
    campo_t* nueva_tabla = malloc(sizeof(campo_t) * capacidad);
	
	if (!nueva_tabla) return NULL;

    for (size_t i = 0; i < capacidad; i++) {
        nueva_tabla[i].estado = VACIO;
        nueva_tabla[i].clave = NULL;
        nueva_tabla[i].dato = NULL;
    }
    return nueva_tabla;
}

bool hash_redimensionar(hash_t* hash, size_t nueva_capacidad) {
	campo_t* tabla_anterior = hash->tabla;
	hash->tabla = hash_inicializar_tabla(hash, nueva_capacidad);

    if (!hash->tabla) return false;

	size_t capacidad_anterior = hash->capacidad;
	hash->capacidad = nueva_capacidad;
    hash->cantidad = 0;
    hash->cant_no_vacios = 0;
    
    size_t indice;
	for (indice = 0; indice < capacidad_anterior; indice++) {
		if (tabla_anterior[indice].estado == OCUPADO) {
			if (!hash_guardar(hash, tabla_anterior[indice].clave, tabla_anterior[indice].dato)) return false;
			free(tabla_anterior[indice].clave);
		}
	}
	
	if (indice != capacidad_anterior) {
		indice = 0;
		while (indice < nueva_capacidad) {
			if (hash->tabla[indice].estado == OCUPADO) {
				free(hash->tabla[indice].clave);
			}
			indice++;
		}
		free(hash->tabla);
		hash->tabla = tabla_anterior;
		return false;
	}
	free(tabla_anterior);
	return true;
}

size_t hash_buscar_campo(const hash_t* hash, const char *clave, size_t posicion) {
    while(hash->tabla[posicion].estado != VACIO){
        if (hash->tabla[posicion].estado == OCUPADO && strcmp(hash->tabla[posicion].clave, clave) == 0){
            return posicion;
        }
        posicion ++;
        if (posicion==hash->capacidad) posicion = 0;
	}
	return posicion;
}

void hash_iter_avanzar_hasta_siguiente_ocupado(hash_iter_t *iter, size_t pos) {
	while(pos<iter->hash->capacidad && iter->hash->tabla[pos].estado!=OCUPADO) pos++;
    iter->posicion=pos;
}

// PRIMITIVAS DEL HASH

hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
    hash_t *hash = malloc(sizeof(hash_t));

    if (!hash) return NULL;

    hash->tabla = hash_inicializar_tabla(hash, CAPACIDAD_INICIAL);

    if (!hash->tabla) {
        free(hash);
        return NULL;
    }
    
    hash->capacidad = CAPACIDAD_INICIAL;
    hash->cantidad = 0;
    hash->destruir_dato = destruir_dato;
    hash->cant_no_vacios = 0;
    
    return hash;
}

bool hash_pertenece(const hash_t *hash, const char *clave){

    unsigned long posicion=funcion_hash((unsigned char*)clave) % hash->capacidad;

    posicion = hash_buscar_campo(hash, clave, posicion);
    if(hash->tabla[posicion].estado==VACIO) return false;
    return true;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
	if (hash->cant_no_vacios * 100 / hash->capacidad >= FACTOR_DE_CARGA * 100) {
		if(!hash_redimensionar(hash, hash->capacidad*CONST_DE_REDIMENSION)) return false;
	}

    unsigned long posicion = funcion_hash((unsigned char*)clave) % hash->capacidad;

    posicion=hash_buscar_campo(hash,clave,posicion);

    if (hash->tabla[posicion].estado==VACIO){

        char* copia_clave = strdup(clave);
        if (!copia_clave) return false;
        hash->tabla[posicion].clave = copia_clave;
        hash->tabla[posicion].dato = dato;
        hash->tabla[posicion].estado = OCUPADO;

        hash->cantidad++;
        hash->cant_no_vacios++;
        return true;
    }else{
        if (hash->destruir_dato) hash->destruir_dato(hash->tabla[posicion].dato);
        hash->tabla[posicion].dato = dato;
        hash->tabla[posicion].estado = OCUPADO;
        return true;
    }
}

void *hash_borrar(hash_t *hash, const char *clave) {
	unsigned long posicion = funcion_hash((unsigned char*)clave) % hash->capacidad;

	if (!hash_pertenece(hash,clave)) return NULL;

    posicion = hash_buscar_campo(hash, clave, posicion);
    
    hash->tabla[posicion].estado=BORRADO;
    void* dato=hash->tabla[posicion].dato;
    free(hash->tabla[posicion].clave);
    hash->cantidad--;
    return dato;
}

void *hash_obtener(const hash_t *hash, const char *clave) {
	unsigned long posicion = funcion_hash((unsigned char*)clave) % hash->capacidad;
	if (!hash_pertenece(hash,clave)) return NULL;

    posicion = hash_buscar_campo(hash, clave, posicion);
	return hash->tabla[posicion].dato;
}

size_t hash_cantidad(const hash_t *hash) {
    return hash->cantidad;
}

void hash_destruir(hash_t *hash) {
    for (int i = 0; i < hash->capacidad; i++){
        if (hash->tabla[i].estado != OCUPADO) {
            continue;
        }
            
        if (hash->destruir_dato) {
            hash->destruir_dato(hash->tabla[i].dato);
        }
        free(hash->tabla[i].clave);
    }
    free(hash->tabla);
    free(hash);
}

//PRIMITIVAS DEL ITERADOR DEL HASH

hash_iter_t *hash_iter_crear(const hash_t *hash){
    hash_iter_t * iterador=malloc(sizeof(hash_iter_t));
    if (!iterador) return NULL;

    iterador->hash=hash;

    size_t pos=0;
    hash_iter_avanzar_hasta_siguiente_ocupado(iterador, pos);
    return iterador;
}

bool hash_iter_al_final(const hash_iter_t *iter){
    return iter->posicion==iter->hash->capacidad;
}

bool hash_iter_avanzar(hash_iter_t *iter){
    size_t pos = iter->posicion +1;

    if (hash_iter_al_final(iter)) return false;

    hash_iter_avanzar_hasta_siguiente_ocupado(iter, pos);
    return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
	if (hash_iter_al_final(iter)) return NULL;
    return iter->hash->tabla[iter->posicion].clave;
}

void hash_iter_destruir(hash_iter_t *iter){
    free(iter);
}

