#include <stdlib.h>
#include "heap.h"
#include <stdio.h>

#define CAPACIDAD_INICIAL 10
#define REDIMENSION 2
#define LIMITE_REDIMENSION 4

struct heap {
    void** arreglo;
    size_t cantidad;
    size_t capacidad;
    cmp_func_t cmp;
};

// FUNCIONES AUXILIARES

bool heap_redimensionar(heap_t *heap, size_t nueva_capacidad) {
    void **nuevo_arreglo = realloc(heap->arreglo, nueva_capacidad * sizeof(void*));
    
    if (!nuevo_arreglo) return false;
    
    heap->arreglo = nuevo_arreglo;
    heap->capacidad = nueva_capacidad;
    return true;
}

size_t buscar_padre(size_t pos) {
    return ((int)pos - 1) / 2;
}

size_t buscar_hijo_izq(size_t pos) {
    return 2 * pos + 1;
}

size_t buscar_hijo_der(size_t pos) {
    return 2 * pos + 2;
}

void swap(void **arreglo, size_t pos_a, size_t pos_b){
    void *aux = arreglo[pos_a];
    arreglo[pos_a] = arreglo[pos_b];
    arreglo[pos_b] = aux;
}

void upheap(void** arreglo, cmp_func_t cmp, size_t pos){
	if (pos == 0) return;
    
    size_t pos_padre = buscar_padre(pos);
	
    if (cmp(arreglo[pos], arreglo[pos_padre]) > 0) {
		swap(arreglo, pos, (size_t)pos_padre);
		upheap(arreglo, cmp, pos_padre);
	}
}

void downheap(void** arreglo, size_t cantidad, cmp_func_t cmp, size_t pos){
    if ((int)pos >= ((int)cantidad)-1) return;
    
    size_t pos_hijo_izq = buscar_hijo_izq(pos);
    size_t pos_hijo_der = buscar_hijo_der(pos);
    size_t pos_max;

    if (pos_hijo_izq >= cantidad) return;

    if (pos_hijo_der < cantidad && cmp(arreglo[pos_hijo_izq], arreglo[pos_hijo_der]) > 0) pos_max = pos_hijo_izq;
    
    else if (pos_hijo_der < cantidad) pos_max = pos_hijo_der;

    else pos_max = pos_hijo_izq;

    if (cmp(arreglo[pos], arreglo[pos_max]) < 0) {
        swap(arreglo, pos, pos_max);
        downheap(arreglo, cantidad, cmp, pos_max);                                                  
    }   
}

void heapify(void** arreglo, size_t cantidad, cmp_func_t cmp) {
    for (size_t i = cantidad ; i > 0; i--) {
        downheap(arreglo, cantidad, cmp, i-1);
    }
}

// PRIMITIVAS DEL HEAP

heap_t *heap_crear(cmp_func_t cmp) {
    heap_t *heap = malloc(sizeof(heap_t));
    if (!heap) return NULL;

    heap->arreglo = malloc(sizeof(void*) * CAPACIDAD_INICIAL);
    if(!heap->arreglo) {
        free(heap);
        return NULL;
    }

    heap->cantidad = 0;
    heap->capacidad = CAPACIDAD_INICIAL;
    heap->cmp = cmp;
    
    return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
    heap_t *heap = heap_crear(cmp);
    if (!heap) return NULL;

    while (n >= heap->capacidad) {
        if (!heap_redimensionar(heap, heap->capacidad * REDIMENSION)) {
            free(heap);
            return NULL;
        }
    }

    for (size_t i = 0; i < n; i++) {
        heap->arreglo[i] = arreglo[i];
    }
    heap->cantidad = n;
    heapify(heap->arreglo, n, cmp);

    return heap;
}

size_t heap_cantidad(const heap_t *heap) {
    return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap) {
    return heap->cantidad == 0;
}

void *heap_ver_max(const heap_t *heap) {
    if (heap_esta_vacio(heap)) return NULL;
    return heap->arreglo[0];
}

bool heap_encolar(heap_t *heap, void *elem){
	if (heap->cantidad == heap->capacidad){
		if (!heap_redimensionar(heap, heap->capacidad * REDIMENSION)) return false;
	}

	heap->arreglo[heap->cantidad] = elem;
	upheap(heap->arreglo, heap->cmp, heap->cantidad);
    heap->cantidad++;
	return true;
}

void *heap_desencolar(heap_t *heap){
	if(heap_esta_vacio(heap)) return NULL;
	
	void *dato = heap->arreglo[0];
	heap->arreglo[0] = heap->arreglo[heap->cantidad - 1];
	heap->cantidad--;
    
    downheap(heap->arreglo, heap->cantidad, heap->cmp, 0);
	
	if (heap->capacidad > heap->cantidad * LIMITE_REDIMENSION){
		heap_redimensionar(heap, heap->capacidad / REDIMENSION);
	}
	return dato;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){
	if (destruir_elemento) {
		for(int i = 0; i < heap->cantidad; i++){
			destruir_elemento(heap->arreglo[i]);
		}
	}
	free(heap->arreglo);
	free(heap);
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
    heapify(elementos, cant, cmp);

    while(cant > 0) {
        swap(elementos, 0, cant-1);
        cant--;
        downheap(elementos, cant, cmp, 0);
    }
}


