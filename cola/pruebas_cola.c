#include "cola.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>

#include "pila.h"


static void prueba_cola_crear_destruir(void) {
    printf("INICIO DE PRUEBA DE CREAR Y DESTRUIR COLA\n");

    cola_t* cola = cola_crear();
    print_test("crear cola", cola != NULL);

    cola_destruir(cola, NULL);
    print_test("la cola fue destruida", true);
    printf("\n");
}

static void prueba_cola_vacia(void) {
	printf("INICIO DE PRUEBAS CON COLA VACIA\n");
	
    cola_t* cola = cola_crear();
    
    print_test("la cola esta vacia", cola_esta_vacia(cola) == true);
    print_test("desencolar es invalido", cola_desencolar(cola) == NULL);
    print_test("ver primero es invalido", cola_ver_primero(cola) == NULL);
    
    cola_destruir(cola, NULL);
    print_test("la cola fue destruida", true);
    printf("\n");
}

static void prueba_cola_encolar_distintos_tipos(void) {
    printf("INICIO DE PRUEBAS DE ENCOLADO DE ELEMENTOS DE DISTINTOS TIPOS\n");

    cola_t* cola = cola_crear();

    int dato1 = 1;
    char dato2 = 'a';
    double dato3 = 3.14;

    print_test("el dato1 fue encolado correctamente", cola_encolar(cola, &dato1));
    print_test("el dato encolado esta primero", cola_ver_primero(cola) == &dato1);
    print_test("el dato fue desencolado correctamente", cola_desencolar(cola) == &dato1);
    print_test("el dato2 fue encolado correctamente", cola_encolar(cola, &dato2));
    print_test("el dato encolado esta primero", cola_ver_primero(cola) == &dato2);
    print_test("el dato fue desencolado correctamente", cola_desencolar(cola) == &dato2);
    print_test("el dato3 fue encolado correctamente", cola_encolar(cola, &dato3));
    print_test("el dato encolado esta primero", cola_ver_primero(cola) == &dato3);
    print_test("el dato fue desencolado correctamente", cola_desencolar(cola) == &dato3);

	print_test("la cola esta vacia", cola_esta_vacia(cola) == true);
	
    cola_destruir(cola, NULL);
    print_test("la cola fue destruida", true);
    printf("\n");
}

static void prueba_cola_invariante(void){
    printf("INICIO DE PRUEBAS DE INVARIANTE\n");

    cola_t* cola = cola_crear();

    int dato1 = 0;
    int dato2 = 1;
    int dato3 = 2;
    int dato4 = 3;
    int dato5 = 4;
    int dato6 = 5;
    int dato7 = 6;
    int dato8 = 7;
    int dato9 = 8;

    print_test("el dato1 fue encolado correctamente", cola_encolar(cola, &dato1));
    print_test("el dato1 esta primero", cola_ver_primero(cola) == &dato1);
    print_test("el dato2 fue encolado correctamente", cola_encolar(cola, &dato2));
    print_test("el dato1 sigue estando primero", cola_ver_primero(cola) == &dato1);
    print_test("el dato1 fue desencolado correctamente", cola_desencolar(cola) == &dato1);
    print_test("el dato2 estan primero", cola_ver_primero(cola) == &dato2);
    print_test("el dato2 fue desencolado correctamente", cola_desencolar(cola) == &dato2);
    
    print_test("el dato3 fue encolado correctamente", cola_encolar(cola, &dato3));
    print_test("el dato3 esta primero", cola_ver_primero(cola) == &dato3);
    print_test("el dato4 fue encolado correctamente", cola_encolar(cola, &dato4));
    print_test("el dato3 sigue estando primero", cola_ver_primero(cola) == &dato3);
    print_test("el dato5 fue encolado correctamente", cola_encolar(cola, &dato5));
    print_test("el dato3 sigue estando primero", cola_ver_primero(cola) == &dato3);
    print_test("el dato3 fue desencolado correctamente", cola_desencolar(cola) == &dato3);
    print_test("el dato4 esta primero", cola_ver_primero(cola) == &dato4);
    print_test("el dato4 fue desencolado correctamente", cola_desencolar(cola) == &dato4);
    print_test("el dato5 esta primero", cola_ver_primero(cola) == &dato5);
    print_test("el dato5 fue desencolado correctamente", cola_desencolar(cola) == &dato5);
    
    print_test("el dato6 fue encolado correctamente", cola_encolar(cola, &dato6));
    print_test("el dato6 esta primero", cola_ver_primero(cola) == &dato6);
    print_test("el dato7 fue encolado correctamente", cola_encolar(cola, &dato7));
    print_test("el dato6 sigue estando primero", cola_ver_primero(cola) == &dato6);
    print_test("el dato8 fue encolado correctamente", cola_encolar(cola, &dato8));
    print_test("el dato6 sigue estando esta primero", cola_ver_primero(cola) == &dato6);
    print_test("el dato9 fue encolado correctamente", cola_encolar(cola, &dato9));
    print_test("el dato6 sigue estando esta primero", cola_ver_primero(cola) == &dato6);
    print_test("el dato6 fue desencolado correctamente", cola_desencolar(cola) == &dato6);
    print_test("el dato7 esta primero", cola_ver_primero(cola) == &dato7);
    print_test("el dato7 fue desencolado correctamente", cola_desencolar(cola) == &dato7);
    print_test("el dato8 esta primero", cola_ver_primero(cola) == &dato8);
    print_test("el dato8 fue desencolado correctamente", cola_desencolar(cola) == &dato8);
    print_test("el dato9 esta primero", cola_ver_primero(cola) == &dato9);
    print_test("el dato9 fue desencolado correctamente", cola_desencolar(cola) == &dato9);

    print_test("la cola esta vacia", cola_esta_vacia(cola));
    
    cola_destruir(cola, NULL);
    print_test("la cola fue destruida", true);
    printf("\n");

}

static void prueba_cola_volumen(void) {
    printf("INICIO DE PRUEBA DE VOLUMEN\n");

    cola_t* cola = cola_crear();

    int* vector = malloc(1000*sizeof(int));
    for (int i = 0; i < 1000; i++) {
        cola_encolar(cola, &vector[i]);
    }

    print_test("ver primer elemento de cola de 1000 elementos", cola_ver_primero(cola) == &vector[0]);
    
    printf("Desencolar 500 elementos\n");
    for (int i = 0; i < 500; i++) {
        cola_desencolar(cola);
    }
    print_test("ver que el elemento 500 esta primero luego de desencolar 500 elementos", cola_ver_primero(cola) == &vector[500]);

    printf("Desencolar hasta quedar vacia\n");
    for (int i = 0; i <= 500; i++) {
        cola_desencolar(cola);
    }
    print_test("la cola esta vacia", cola_esta_vacia(cola));
    
    cola_destruir(cola, NULL);
    print_test("la cola fue destruida", true);
    
    free(vector);
    printf("\n");
}

static void prueba_cola_encolar_NULL(void) {
    printf("INICIO DE PRUEBA DE ENCOLAR NULL\n");

    cola_t* cola = cola_crear();

    print_test("guarda el elemento NULL", cola_encolar(cola, NULL));
    print_test("la cola deberia contener NULL", cola_ver_primero(cola) == NULL);
    print_test("la cola no deberia estar vacia", !cola_esta_vacia(cola));

    cola_destruir(cola, NULL);
    print_test("la cola fue destruida", true);
    printf("\n");

}

static void prueba_cola_desencolar_hasta_vacia(void) {
    printf("INICIO DE PRUEBAS DE DESENCOLAR HASTA VACIAR Y VER SU COMPORTAMIENTO\n");

    cola_t* cola = cola_crear();

    int dato1 = 0;
    int dato2 = 1;

    print_test("el dato1 fue encolado correctamente", cola_encolar(cola, &dato1));
    print_test("el dato2 fue encolado correctamente", cola_encolar(cola, &dato2));
    print_test("el primer dato encolado esta primero", cola_ver_primero(cola) == &dato1);
    print_test("el dato fue desencolado correctamente", cola_desencolar(cola) == &dato1);
    print_test("el dato fue desencolado correctamente", cola_desencolar(cola) == &dato2);
    print_test("la cola esta vacia", cola_esta_vacia(cola) == true);
    print_test("desencolar es invalido", cola_desencolar(cola) == NULL);
    print_test("ver el primero es invalido", cola_ver_primero(cola) == NULL);
    
    cola_destruir(cola, NULL);
    print_test("la cola fue destruida", true);
    printf("\n");
}


static void prueba_cola_destruir_con_free(void) {
    printf("INICIO DE PRUEBA DE DESTRUID CON LA FUNCION FREE\n");
    cola_t* cola = cola_crear();
    int* vector1 = malloc(sizeof(int));
    int* vector2 = malloc(sizeof(int));
    int* vector3 = malloc(sizeof(int));
    
    print_test("el vector1 fue encolado correctamente", cola_encolar(cola, vector1));
    print_test("el vector2 fue encolado correctamente", cola_encolar(cola, vector2));
    print_test("el vector3 fue encolado correctamente", cola_encolar(cola, vector3));
    cola_destruir(cola, free);
    print_test("la cola fue destruida", true);
    printf("\n");

}


void destruir_pila(void* pila) {
	pila_destruir((pila_t *) pila);
}

static void prueba_cola_destruir_pila(void) {
    printf("INICIO DE PRUEBA DE DESTRUID COLA CON PILAS\n");
    cola_t* cola = cola_crear();
    pila_t* pila1 = pila_crear();
    pila_t* pila2 = pila_crear();
    pila_t* pila3 = pila_crear();

    print_test("la pial1 fue encolado correctamente", cola_encolar(cola, pila1));
    print_test("la pila2 fue encolado correctamente", cola_encolar(cola, pila2));
    print_test("la pila3 fue encolado correctamente", cola_encolar(cola, pila3));
    cola_destruir(cola, destruir_pila);
    print_test("la cola fue destruida", true);
    printf("\n");

}


void destruir_cola(void* cola){
	cola_destruir((cola_t*) cola, NULL);
}

static void prueba_cola_destruir_cola(void) {
    printf("INICIO DE PRUEBA DE DESTRUID COLA CON COLAS\n");
    cola_t* cola = cola_crear();
    cola_t* nueva_cola1 = cola_crear();
    cola_t* nueva_cola2 = cola_crear();
    cola_t* nueva_cola3 = cola_crear();

    print_test("la cola1 fue encolado correctamente", cola_encolar(cola, nueva_cola1));
    print_test("la cola2 fue encolado correctamente", cola_encolar(cola, nueva_cola2));
    print_test("la cola3 fue encolado correctamente", cola_encolar(cola, nueva_cola3));
    cola_destruir(cola, destruir_cola);
    print_test("la cola fue destruida", true);
    printf("\n");
}

void pruebas_cola_estudiante() {
	prueba_cola_crear_destruir();
    prueba_cola_vacia();
    prueba_cola_encolar_distintos_tipos();
    prueba_cola_invariante();
    prueba_cola_volumen();
    prueba_cola_encolar_NULL();
    prueba_cola_desencolar_hasta_vacia();
    prueba_cola_destruir_con_free();
    prueba_cola_destruir_pila();
    prueba_cola_destruir_cola();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
