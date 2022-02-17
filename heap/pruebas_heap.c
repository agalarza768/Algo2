#include "heap.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// FUNCIONES AUXILIARES

int comparar_num(const int* a, const int* b){
	if (*a>*b) return 1;
	if (*a<*b) return -1;
	return 0;
}

// PRUEBAS

static void prueba_crear_heap_vacio() {
    heap_t* heap = heap_crear((cmp_func_t)strcmp);

    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap esta vacio",heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap desencolar es NULL", !heap_desencolar(heap));
    print_test("Prueba heap ver max es NULL", !heap_ver_max(heap));

    heap_destruir(heap,NULL);
}

static void prueba_heap_encolar_y_desencolar_algunos_elementos() {
    heap_t* heap = heap_crear((cmp_func_t)strcmp);

    char *elem1="a" , *elem2="b" , *elem3="c" , *elem4="d" , *elem5="e";

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba heap encolar elem3", heap_encolar(heap, elem3));
    print_test("Prueba heap encolar elem4", heap_encolar(heap, elem4));
    print_test("Prueba heap encolar elem2", heap_encolar(heap, elem2));
    print_test("Prueba heap encolar elem5", heap_encolar(heap, elem5));
    print_test("Prueba heap encolar elem1", heap_encolar(heap, elem1));

    print_test("La cantidad de elementos del heap es 5",heap_cantidad(heap)==5);
    print_test("El heap no esta vacio",!heap_esta_vacio(heap));

    char *maximo=heap_ver_max(heap);
    print_test("El elem5 es el maximo del heap",strcmp(maximo,elem5)==0);
    maximo=heap_desencolar(heap);
    print_test("Desencolar el heap me devuelve el elem5",strcmp(maximo,elem5)==0);

    maximo=heap_ver_max(heap);
    print_test("El elem4 es el maximo del heap",strcmp(maximo,elem4)==0);
    maximo=heap_desencolar(heap);
    print_test("Desencolar el heap me devuelve el elem4",strcmp(maximo,elem4)==0);

    maximo=heap_ver_max(heap);
    print_test("El elem3 es el maximo del heap",strcmp(maximo,elem3)==0);
    maximo=heap_desencolar(heap);
    print_test("Desencolar el heap me devuelve el elem3",strcmp(maximo,elem3)==0);

    maximo=heap_ver_max(heap);
    print_test("El elem2 es el maximo del heap",strcmp(maximo,elem2)==0);
    maximo=heap_desencolar(heap);
    print_test("Desencolar el heap me devuelve el elem2",strcmp(maximo,elem2)==0);

    maximo=heap_ver_max(heap);
    print_test("El elem1 es el maximo del heap",strcmp(maximo,elem1)==0);
    maximo=heap_desencolar(heap);
    print_test("Desencolar el heap me devuelve el elem1",strcmp(maximo,elem1)==0);

    print_test("Heap ver maximo es NULL",!heap_ver_max(heap));
    print_test("Desencolar el heap me devuelve NULL",!heap_desencolar(heap));
    print_test("El heap quedo vacio", heap_esta_vacio(heap));
    print_test("La cantidad del heap es 0", heap_cantidad(heap)==0);

    heap_destruir(heap, NULL);
}

static void prueba_heap_volumen(size_t largo) {
    heap_t *heap = heap_crear((cmp_func_t)comparar_num);
    
    int* arreglo = malloc(largo * sizeof(int));
    for(size_t i = 0; i < largo; i++){
		arreglo[i] = rand();
	}
	
	bool ok = true;
    for (size_t i = 0; i < largo; i++) {
		if (!heap_encolar(heap, &arreglo[i])) {
			ok = false;
			break;
		}
    }
	
	print_test("Todos los elementos fueron encolados correctamente", ok);
    print_test("Prueba heap la cantidad de elementos del heap es correcta",heap_cantidad(heap) == largo);
    print_test("Prueba heap no esta vacio",!heap_esta_vacio(heap));
    
    ok = true;
    int *desencolado = heap_desencolar(heap);
    for (size_t i = 0; i < largo-1; i++) {
        int *max = heap_ver_max(heap);
        if (comparar_num(desencolado, max) < 0) {
			ok = false;
			break;
		}
		desencolado = heap_desencolar(heap);
    }
    
    print_test("Todos los elementos fueron desencolados correctamente", ok);
    print_test("El heap esta vacio", heap_esta_vacio(heap));
    
    heap_destruir(heap, NULL);
    print_test("El heap fue destruido", true);
    
    free(arreglo);
}

static void prueba_heap_encolar_NULL(void) {
    heap_t *heap = heap_crear((cmp_func_t)comparar_num);

    print_test("Guarda el elemento NULL", heap_encolar(heap, NULL));
    print_test("El heap deberia contener NULL", heap_ver_max(heap) == NULL);
    print_test("El heap no deberia estar vacio", !heap_esta_vacio(heap));

    heap_destruir(heap, NULL);
}

static void prueba_heap_con_destruccion() {
    heap_t* heap = heap_crear((cmp_func_t)comparar_num);

    int* elem1 = malloc(sizeof(int));
    int* elem2 = malloc(sizeof(int));
    int* elem3 = malloc(sizeof(int));

    *elem1 = 2;
    *elem2 = 8;
    *elem3 = 6;

    print_test("Prueba heap encolar elem1", heap_encolar(heap, elem1));
    print_test("Prueba heap encolar elem2", heap_encolar(heap, elem2));
    print_test("Prueba heap encolar elem3", heap_encolar(heap, elem3));

    print_test("La cantidad de elementos del heap es 3", heap_cantidad(heap) == 3);
    print_test("El heap no esta vacio", !heap_esta_vacio(heap));

    heap_destruir(heap, free);
    print_test("El heap fue destruido y los elementos fueron liberados", true);
}

static void prueba_crear_heap_con_arreglo() {
    size_t largo = 5;
    void *arreglo[largo];
    int elem1 = 1, elem2 = 2, elem3 = 3, elem4 = 4 , elem5 = 5;

    arreglo[0] = &elem3;
    arreglo[1] = &elem1;
    arreglo[2] = &elem5;
    arreglo[3] = &elem4;
    arreglo[4] = &elem2;

    heap_t* heap = heap_crear_arr(arreglo, largo, (cmp_func_t)comparar_num);

    print_test("Prueba heap crear heap con arreglo", heap);
    print_test("Prueba heap no esta vacio", !heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es 5", heap_cantidad(heap) == 5);
    
    print_test("El elem5 es el maximo del heap", heap_ver_max(heap) == &elem5);
    print_test("Desencolar el heap me devuelve el elem5", heap_desencolar(heap) == &elem5);

    print_test("El elem4 es el maximo del heap", heap_ver_max(heap) == &elem4);
    print_test("Desencolar el heap me devuelve el elem4", heap_desencolar(heap) == &elem4);

    print_test("El elem3 es el maximo del heap", heap_ver_max(heap) == &elem3);
    print_test("Desencolar el heap me devuelve el elem3", heap_desencolar(heap) == &elem3);

    print_test("El elem2 es el maximo del heap", heap_ver_max(heap) == &elem2);
    print_test("Desencolar el heap me devuelve el elem2", heap_desencolar(heap) == &elem2);

    print_test("El elem1 es el maximo del heap", heap_ver_max(heap) == &elem1);
    print_test("Desencolar el heap me devuelve el elem1", heap_desencolar(heap) == &elem1);

    print_test("El heap quedo vacio", heap_esta_vacio(heap));
    print_test("La cantidad del heap es 0", heap_cantidad(heap) == 0);

    heap_destruir(heap, NULL);
}

static void prueba_heapsort() {
    size_t largo = 5;
    void *arreglo[largo];
    int elem1 = 1, elem2 = 2, elem3 = 3, elem4 = 4 , elem5 = 5;

    arreglo[0] = &elem3;
    arreglo[1] = &elem1;
    arreglo[2] = &elem5;
    arreglo[3] = &elem4;
    arreglo[4] = &elem2;
    
    heap_sort(arreglo, largo, (cmp_func_t)comparar_num);

    int* anterior = arreglo[0];
    bool esta_ordenado = true;
    for (size_t i = 1; i < largo; i++) {
        if(comparar_num(anterior, arreglo[i])>0) {
            esta_ordenado = false;
            break;
        }
        anterior=arreglo[i];
    }
    print_test("El arreglo fue ordenado correctamente", esta_ordenado);
}


void pruebas_heap_estudiante(){
	prueba_crear_heap_vacio();
	prueba_heap_encolar_y_desencolar_algunos_elementos();
	prueba_heap_volumen(5000);
    prueba_heap_encolar_NULL();
    prueba_heap_con_destruccion();
    prueba_crear_heap_con_arreglo();
    prueba_heapsort();
}

#ifndef CORRECTOR

int main(void) {
	pruebas_heap_estudiante();
	return failure_count() > 0;
}

#endif
