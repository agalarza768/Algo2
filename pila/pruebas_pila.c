#include "pila.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>


static void prueba_pila_crear_destruir(void) {
    printf("INICIO DE PRUEBA DE CREAR Y DESTRUIR PILA\n");

    pila_t* pila = pila_crear();
    print_test("crear pila", pila != NULL);

    pila_destruir(pila);
    print_test("la pila fue destruida", true);
    printf("\n");
}

static void prueba_pila_vacia(void) {
	printf("INICIO DE PRUEBAS CON PILA VACIA\n");
	
    pila_t *pila = pila_crear();
    
    print_test("la pila esta vacia", pila_esta_vacia(pila) == true);
    print_test("desapilar es invalido", pila_desapilar(pila) == NULL);
    print_test("ver tope es invalido", pila_ver_tope(pila) == NULL);
    
    pila_destruir(pila);
    print_test("la pila fue destruida", true);
    printf("\n");
}

static void prueba_pila_apilar_distintos_tipos(void) {
    printf("INICIO DE PRUEBAS DE APILADO DE ELEMENTOS DE DISTINTOS TIPOS\n");

    pila_t* pila = pila_crear();

    int dato1 = 1;
    char dato2[] = "hola";
    double dato3 = 3.14;

    print_test("el dato1 fue apilado correctamente", pila_apilar(pila, &dato1));
    print_test("el dato apilado esta en el tope", pila_ver_tope(pila) == &dato1);
    print_test("el dato fue desapilado correctamente", pila_desapilar(pila) == &dato1);
    print_test("el dato2 fue apilado correctamente", pila_apilar(pila, &dato2));
    print_test("el dato apilado esta en el tope", pila_ver_tope(pila) == &dato2);
    print_test("el dato fue desapilado correctamente", pila_desapilar(pila) == &dato2);
    print_test("el dato3 fue apilado correctamente", pila_apilar(pila, &dato3));
    print_test("el dato apilado esta en el tope", pila_ver_tope(pila) == &dato3);
    print_test("el dato fue desapilado correctamente", pila_desapilar(pila) == &dato3);

	print_test("la pila esta vacia", pila_esta_vacia(pila) == true);
	
    pila_destruir(pila);
    print_test("la pila fue destruida", true);
    printf("\n");
}

static void prueba_pila_invariante(void){
    printf("INICIO DE PRUEBAS DE INVARIANTE\n");

    pila_t* pila = pila_crear();

    int dato1 = 0;
    int dato2 = 1;
    int dato3 = 2;
    int dato4 = 3;
    int dato5 = 4;
    int dato6 = 5;
    int dato7 = 6;
    int dato8 = 7;
    int dato9 = 8;

    print_test("el dato1 fue apilado correctamente", pila_apilar(pila, &dato1));
    print_test("el dato apilado esta en el tope", pila_ver_tope(pila) == &dato1);
    print_test("el dato2 fue apilado correctamente", pila_apilar(pila, &dato2));
    print_test("el dato apilado esta en el tope", pila_ver_tope(pila) == &dato2);
    print_test("el dato2 fue desapilado correctamente", pila_desapilar(pila) == &dato2);
    print_test("el dato1 fue desapilado correctamente", pila_desapilar(pila) == &dato1);
    
    print_test("el dato3 fue apilado correctamente", pila_apilar(pila, &dato3));
    print_test("el dato apilado esta en el tope", pila_ver_tope(pila) == &dato3);
    print_test("el dato4 fue apilado correctamente", pila_apilar(pila, &dato4));
    print_test("el dato apilado esta en el tope", pila_ver_tope(pila) == &dato4);
    print_test("el dato5 fue apilado correctamente", pila_apilar(pila, &dato5));
    print_test("el dato apilado esta en el tope", pila_ver_tope(pila) == &dato5);
    print_test("el dato5 fue desapilado correctamente", pila_desapilar(pila) == &dato5);
    print_test("el dato4 fue desapilado correctamente", pila_desapilar(pila) == &dato4);
    print_test("el dato3 fue desapilado correctamente", pila_desapilar(pila) == &dato3);
    
    print_test("el dato6 fue apilado correctamente", pila_apilar(pila, &dato6));
    print_test("el dato apilado esta en el tope", pila_ver_tope(pila) == &dato6);
    print_test("el dato7 fue apilado correctamente", pila_apilar(pila, &dato7));
    print_test("el dato apilado esta en el tope", pila_ver_tope(pila) == &dato7);
    print_test("el dato8 fue apilado correctamente", pila_apilar(pila, &dato8));
    print_test("el dato apilado esta en el tope", pila_ver_tope(pila) == &dato8);
    print_test("el dato9 fue apilado correctamente", pila_apilar(pila, &dato9));
    print_test("el dato apilado esta en el tope", pila_ver_tope(pila) == &dato9);
    print_test("el dato9 fue desapilado correctamente", pila_desapilar(pila) == &dato9);
    print_test("el dato8 fue desapilado correctamente", pila_desapilar(pila) == &dato8);
    print_test("el dato7 fue desapilado correctamente", pila_desapilar(pila) == &dato7);
    print_test("el dato6 fue desapilado correctamente", pila_desapilar(pila) == &dato6);

    print_test("la pila esta vacia", pila_esta_vacia(pila));
    
    pila_destruir(pila);
    print_test("la pila fue destruida", true);
    printf("\n");
}

static void prueba_pila_volumen(void) {
    printf("INICIO DE PRUEBA DE VOLUMEN\n");

    pila_t* pila = pila_crear();

    int* vector = malloc(1000*sizeof(int));
    for (int i = 0; i <= 1000; i++) {
        pila_apilar(pila, &vector[i]);
    }

    print_test("ver tope de pila de 1000 elementos", pila_ver_tope(pila) == &vector[1000]);
    
    printf("Desapila 500 elementos\n");
    for (int i = 0; i < 500; i++) {
        pila_desapilar(pila);
    }
    print_test("ver tope de pila de 500 elementos", pila_ver_tope(pila) == &vector[500]);

    printf("Desapila hasta quedar vacia\n");
    for (int i = 0; i <= 500; i++) {
        pila_desapilar(pila);
    }
    print_test("pila esta vacia", pila_esta_vacia(pila));
    
    pila_destruir(pila);
    print_test("la pila fue destruida", true);
    
    free(vector);
    printf("\n");
}

static void prueba_pila_apilar_NULL(void) {
    printf("INICIO DE PRUEBA DE APILAR NULL\n");

    pila_t* pila = pila_crear();

    print_test("guarda el elemento NULL", pila_apilar(pila, NULL));
    print_test("la pila deberia seguir vacia", pila_ver_tope(pila) == NULL);

    pila_destruir(pila);
    print_test("la pila fue destruida", true);
    printf("\n");
}

static void prueba_pila_desapilar_hasta_vacia(void) {
    printf("INICIO DE PRUEBAS DE DESAPILAR HASTA VACIAR PARA VER COMPORTAMIENTO\n");

    pila_t* pila = pila_crear();

    int dato1 = 0;
    int dato2 = 1;

    print_test("el dato1 fue apilado correctamente", pila_apilar(pila, &dato1));
    print_test("el dato2 fue apilado correctamente", pila_apilar(pila, &dato2));
    print_test("el dato apilado esta en el tope", pila_ver_tope(pila) == &dato2);
    print_test("el dato fue desapilado correctamente", pila_desapilar(pila) == &dato2);
    print_test("el dato fue desapilado correctamente", pila_desapilar(pila) == &dato1);
    print_test("la pila esta vacia", pila_esta_vacia(pila) == true);
    print_test("desapilar es invalido", pila_desapilar(pila) == NULL);
    print_test("ver el tope es invalido", pila_ver_tope(pila) == NULL);
    
    pila_destruir(pila);
    print_test("la pila fue destruida", true);
    printf("\n");
}

void pruebas_pila_estudiante() {
	prueba_pila_crear_destruir();
    prueba_pila_vacia();
    prueba_pila_apilar_distintos_tipos();
    prueba_pila_invariante();
    prueba_pila_volumen();
    prueba_pila_apilar_NULL();
    prueba_pila_desapilar_hasta_vacia();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
