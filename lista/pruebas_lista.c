#include "lista.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>

#include "pila.h"


static void prueba_lista_crear_destruir(void) {
    printf("INICIO DE PRUEBA DE CREAR Y DESTRUIR LISTA\n");

    lista_t* lista = lista_crear();
    print_test("crear lista", lista != NULL);
    print_test("la lista esta vacia", lista_esta_vacia(lista));
    print_test("el primero de la lista es NULL", lista_ver_primero(lista) == NULL);
    print_test("el ultimo de la lista es NULL", lista_ver_ultimo(lista) == NULL);

    lista_destruir(lista, NULL);
    print_test("la lista fue destruida", true);
    printf("\n");
}

static void prueba_lista_vacia(void) {
	printf("INICIO DE PRUEBAS CON LISTA VACIA\n");
	
    lista_t* lista = lista_crear();
    
    print_test("la lista esta vacia", lista_esta_vacia(lista));
    print_test("borrar primero es invalido", lista_borrar_primero(lista) == NULL);
    print_test("ver primero es invalido", lista_ver_primero(lista) == NULL);
    print_test("ver ultimo es invalido", lista_ver_ultimo(lista) == NULL);
    
    lista_destruir(lista, NULL);
    print_test("la lista fue destruida", true);
    printf("\n");
}

static void prueba_lista_insertar_distintos_tipos(void) {
    printf("INICIO DE PRUEBAS DE INSERTADO DE ELEMENTOS DE DISTINTOS TIPOS\n");

    lista_t* lista = lista_crear();

    int dato1 = 1;
    char dato2 = 'a';
    double dato3 = 3.14;

    print_test("el dato1 fue insertado correctamente", lista_insertar_ultimo(lista, &dato1));
    print_test("el dato insertado esta primero", lista_ver_primero(lista) == &dato1);
    print_test("el dato fue borrado correctamente", lista_borrar_primero(lista) == &dato1);
    print_test("el dato2 fue insertado correctamente", lista_insertar_ultimo(lista, &dato2));
    print_test("el dato insertado esta primero", lista_ver_primero(lista) == &dato2);
    print_test("el dato fue borrado correctamente", lista_borrar_primero(lista) == &dato2);
    print_test("el dato3 fue insertado correctamente", lista_insertar_ultimo(lista, &dato3));
    print_test("el dato insertado esta primero", lista_ver_primero(lista) == &dato3);
    print_test("el dato fue borrado correctamente", lista_borrar_primero(lista) == &dato3);
    print_test("ver_primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("ver_ultimo es NULL", lista_ver_ultimo(lista) == NULL);
	print_test("la lista esta vacia", lista_esta_vacia(lista) == true);
	
    lista_destruir(lista, NULL);
    print_test("la lista fue destruida", true);
    printf("\n");
}

static void prueba_lista_invariante(void){
    printf("INICIO DE PRUEBAS DE INVARIANTE\n");

    lista_t* lista = lista_crear();

    int dato1 = 0;
    int dato2 = 1;
    int dato3 = 2;
    int dato4 = 3;
    int dato5 = 4;
    int dato6 = 5;
    int dato7 = 6;
    int dato8 = 7;

    print_test("el dato1 fue insertado al principio correctamente", lista_insertar_primero(lista, &dato1));
    print_test("la lista tiene 1 elemento", lista_largo(lista) == 1);
    print_test("el dato1 esta primero", lista_ver_primero(lista) == &dato1);
    print_test("el dato1 esta ultimo", lista_ver_ultimo(lista) == &dato1);
    print_test("el dato2 fue insertado al principio correctamente", lista_insertar_primero(lista, &dato2));
    print_test("la lista tiene 2 elementos", lista_largo(lista) == 2);
    print_test("el dato2 esta primero", lista_ver_primero(lista) == &dato2);
    print_test("el dato1 esta ultimo", lista_ver_ultimo(lista) == &dato1);
    print_test("el dato2 fue borrado correctamente", lista_borrar_primero(lista) == &dato2);
    print_test("la lista tiene 1 elemento", lista_largo(lista) == 1);
    print_test("el dato1 esta primero", lista_ver_primero(lista) == &dato1);
    print_test("el dato1 sigue estando ultimo", lista_ver_ultimo(lista) == &dato1);
    print_test("el dato1 fue borrado correctamente", lista_borrar_primero(lista) == &dato1);
    print_test("la lista tiene 0 elementos", lista_largo(lista) == 0);
    print_test("ver_primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("ver_ultimo es NULL", lista_ver_ultimo(lista) == NULL);
    
    print_test("el dato3 fue insertado al final correctamente", lista_insertar_ultimo(lista, &dato3));
    print_test("la lista tiene 1 elemento", lista_largo(lista) == 1);
    print_test("el dato3 esta primero", lista_ver_primero(lista) == &dato3);
    print_test("el dato3 esta ultimo", lista_ver_ultimo(lista) == &dato3);
    print_test("el dato4 fue insertado al final correctamente", lista_insertar_ultimo(lista, &dato4));
    print_test("la lista tiene 2 elemento", lista_largo(lista) == 2);
    print_test("el dato3 sigue estando primero", lista_ver_primero(lista) == &dato3);
    print_test("el dato4 esta ultimo", lista_ver_ultimo(lista) == &dato4);
    print_test("el dato3 fue borrado correctamente", lista_borrar_primero(lista) == &dato3);
    print_test("la lista tiene 1 elemento", lista_largo(lista) == 1);
    print_test("el dato4 esta primero", lista_ver_primero(lista) == &dato4);
    print_test("el dato4 esta ultimo", lista_ver_ultimo(lista) == &dato4);
    print_test("el dato4 fue borrado correctamente", lista_borrar_primero(lista) == &dato4);
    print_test("la lista tiene 0 elementos", lista_largo(lista) == 0);
    print_test("ver_primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("ver_ultimo es NULL", lista_ver_ultimo(lista) == NULL);
    
    print_test("el dato5 fue insertado al principio correctamente", lista_insertar_primero(lista, &dato5));
    print_test("la lista tiene 1 elemento", lista_largo(lista) == 1);
    print_test("el dato5 esta primero", lista_ver_primero(lista) == &dato5);
    print_test("el dato5 esta ultimo", lista_ver_ultimo(lista) == &dato5);
    print_test("el dato6 fue insertado al final correctamente", lista_insertar_ultimo(lista, &dato6));
    print_test("la lista tiene 2 elemento", lista_largo(lista) == 2);
    print_test("el dato5 sigue estando primero", lista_ver_primero(lista) == &dato5);
    print_test("el dato6 esta ultimo", lista_ver_ultimo(lista) == &dato6);
    print_test("el dato7 fue insertado al principio correctamente", lista_insertar_primero(lista, &dato7));
    print_test("la lista tiene 3 elemento", lista_largo(lista) == 3);
    print_test("el dato7 esta primero", lista_ver_primero(lista) == &dato7);
    print_test("el dato6 sigue estando ultimo", lista_ver_ultimo(lista) == &dato6);
    print_test("el dato8 fue insertado al final correctamente", lista_insertar_ultimo(lista, &dato8));
    print_test("la lista tiene 4 elemento", lista_largo(lista) == 4);
    print_test("el dato7 sigue estando esta primero", lista_ver_primero(lista) == &dato7);
    print_test("el dato8 esta ultimo", lista_ver_ultimo(lista) == &dato8);
    print_test("el dato7 fue borrado correctamente", lista_borrar_primero(lista) == &dato7);
    print_test("el dato5 esta primero", lista_ver_primero(lista) == &dato5);
    print_test("el dato5 fue borrado correctamente", lista_borrar_primero(lista) == &dato5);
    print_test("el dato6 esta primero", lista_ver_primero(lista) == &dato6);
    print_test("el dato6 fue borrado correctamente", lista_borrar_primero(lista) == &dato6);
    print_test("el dato8 esta primero", lista_ver_primero(lista) == &dato8);
    print_test("el dato8 fue borrado correctamente", lista_borrar_primero(lista) == &dato8);
    print_test("ver_primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("ver_ultimo es NULL", lista_ver_ultimo(lista) == NULL);

    print_test("la lista esta vacia", lista_esta_vacia(lista));
    
    lista_destruir(lista, NULL);
    print_test("la lista fue destruida", true);
    printf("\n");

}

static void prueba_lista_volumen(void) {
    printf("INICIO DE PRUEBA DE VOLUMEN\n");

    lista_t* lista = lista_crear();

    int* vector = malloc(1000*sizeof(int));
    for (int i = 0; i < 1000; i++) {
        lista_insertar_ultimo(lista, &vector[i]);
    }

    print_test("la lista tiene 1000 elemento", lista_largo(lista) == 1000);
    print_test("ver primer elemento de lista de 1000 elementos", lista_ver_primero(lista) == &vector[0]);
    print_test("ver ultimo elemento de lista de 1000 elementos", lista_ver_ultimo(lista) == &vector[999]);

    printf("Borrar 500 elementos\n");
    for (int i = 0; i < 500; i++) {
        lista_borrar_primero(lista);
    }
    print_test("ver que el elemento 500 esta primero luego de borrar 500 elementos", lista_ver_primero(lista) == &vector[500]);

    printf("Borrar hasta quedar vacia\n");
    for (int i = 0; i <= 500; i++) {
        lista_borrar_primero(lista);
    }

    print_test("ver_primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("ver_ultimo es NULL", lista_ver_ultimo(lista) == NULL);
    print_test("la lista esta vacia", lista_esta_vacia(lista));
    
    lista_destruir(lista, NULL);
    print_test("la lista fue destruida", true);
    
    free(vector);
    printf("\n");
}

static void prueba_lista_insertar_NULL(void) {
    printf("INICIO DE PRUEBA DE INSERTAR NULL\n");

    lista_t* lista = lista_crear();

    print_test("guarda el elemento NULL", lista_insertar_ultimo(lista, NULL));
    print_test("ver_primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("ver_ultimo es NULL", lista_ver_ultimo(lista) == NULL);

    lista_destruir(lista, NULL);
    print_test("la lista fue destruida", true);
    printf("\n");
}

static void prueba_lista_borrar_hasta_vacia(void) {
    printf("INICIO DE PRUEBAS DE BORRAR HASTA VACIAR Y VER SU COMPORTAMIENTO\n");

    lista_t* lista = lista_crear();

    int dato1 = 0;
    int dato2 = 1;

    print_test("el dato1 fue insertado correctamente", lista_insertar_ultimo(lista, &dato1));
    print_test("el dato2 fue insertado correctamente", lista_insertar_ultimo(lista, &dato2));
    print_test("el primer dato insertado esta primero", lista_ver_primero(lista) == &dato1);
    print_test("el dato fue borrado correctamente", lista_borrar_primero(lista) == &dato1);
    print_test("el dato fue borrado correctamente", lista_borrar_primero(lista) == &dato2);
    print_test("la lista esta vacia", lista_esta_vacia(lista) == true);
    print_test("borrar es invalido", lista_borrar_primero(lista) == NULL);
    print_test("ver_primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("ver_ultimo es NULL", lista_ver_ultimo(lista) == NULL);

    lista_destruir(lista, NULL);
    print_test("la lista fue destruida", true);
    printf("\n");
}


static void prueba_lista_destruir_con_free(void) {
    printf("INICIO DE PRUEBA DE DESTRUIR CON LA FUNCION FREE\n");
    lista_t* lista = lista_crear();
    int* vector1 = malloc(sizeof(int));
    int* vector2 = malloc(sizeof(int));
    
    print_test("el vector1 fue insertado correctamente", lista_insertar_ultimo(lista, vector1));
    print_test("el vector2 fue insertado correctamente", lista_insertar_ultimo(lista, vector2));
    lista_destruir(lista, free);
    print_test("la lista fue destruida", true);
    printf("\n");

}


void destruir_pila(void* pila) {
	pila_destruir((pila_t *) pila);
}

static void prueba_lista_destruir_pila(void) {
    printf("INICIO DE PRUEBA DE DESTRUID LISTA CON PILAS\n");
    lista_t* lista = lista_crear();
    pila_t* pila1 = pila_crear();
    pila_t* pila2 = pila_crear();

    print_test("la pial1 fue insertado correctamente", lista_insertar_ultimo(lista, pila1));
    print_test("la pila2 fue insertado correctamente", lista_insertar_ultimo(lista, pila2));
    lista_destruir(lista, destruir_pila);
    print_test("la lista fue destruida", true);
    printf("\n");

}

static void prueba_lista_destruccion_de_vacias(void) {
    printf("INICIO DE PRUEBA DE DESTRUCCION DE LISTAS VACIAS\n");
    lista_t* lista1 = lista_crear();
    lista_t* lista2 = lista_crear();

    printf("Pruebo destruir lista1 con funcion de destruccion NULL\n");
    lista_destruir(lista1, NULL);
    print_test("la lista fue destruida", true);

    printf("Pruebo destruir lista2 con funcion de destruccion no NULL\n");
    lista_destruir(lista2, free);
    print_test("la lista fue destruida", true);
    printf("\n");
}

static void prueba_lista_destruccion_de_no_vacia_con_NULL(void) {
    printf("INICIO DE PRUEBA DE DESTRUCCION DE LISTAS NO VACIA CON FUNCION DE DESTRUCCION NULL\n");

    lista_t* lista = lista_crear();

    int dato1 = 0;
    int dato2 = 1;

    print_test("el dato1 fue insertado correctamente", lista_insertar_ultimo(lista, &dato1));
    print_test("el dato2 fue insertado correctamente", lista_insertar_ultimo(lista, &dato2));


    lista_destruir(lista, NULL);
    print_test("la lista fue destruida", true);
    printf("\n");
}


// PRUEBAS DE ITERADOR EXTERNO

static void prueba_iter_externo_insertar(void) {
    printf("INICIO DE PRUEBAS DE INSERTAR CON ITERADOR EXTERNO\n");

    lista_t* lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("crear iterador", iter != NULL);

    int dato1 = 0;
    int dato2 = 1;

    print_test("el dato1 es insertado al principio de la lista", lista_iter_insertar(iter, &dato1));
    print_test("el dato1 esta guardado al principio de la lista", lista_ver_primero(lista) == &dato1);
    print_test("el iterador avanza una posicion", lista_iter_avanzar(iter));
    print_test("el iterador esta al final de la lista", lista_iter_al_final(iter));
    print_test("el dato2 es insertado al final de la lista", lista_iter_insertar(iter, &dato2));
    print_test("el dato2 esta guardado al final de la lista", lista_ver_ultimo(lista) == &dato2);

    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
    printf("\n");
}

static void prueba_iter_externo_remover(void) {
    printf("INICIO DE PRUEBAS DE REMOVER CON ITERADOR EXTERNO\n");
    lista_t* lista = lista_crear();
    
    int dato1 = 0;
    int dato2 = 1;
    int dato3 = 2;

    lista_insertar_ultimo(lista, &dato1);
    lista_insertar_ultimo(lista, &dato2);
    lista_insertar_ultimo(lista, &dato3);

    print_test("se insertaron 3 elementos", lista_largo(lista) == 3);

    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("crear iterador", iter != NULL);

    printf("Remuevo el elemento cuando se crea el iterador\n");
    print_test("el dato1 esta guardado al principio de la lista", lista_ver_primero(lista) == &dato1);
    print_test("el dato1 fue removido correctamente", lista_iter_borrar(iter) == &dato1);
    print_test("el dato2 pasa a estar al principio de la lista", lista_ver_primero(lista) == &dato2);
    
    printf("Itero hasta el ultimo elemento\n");
    lista_iter_avanzar(iter);
    print_test("el dato3 esta guardado al final de la lista", lista_ver_ultimo(lista) == &dato3);
    print_test("el dato3 fue removido correctamente", lista_iter_borrar(iter) == &dato3);
    print_test("el dato2 pasa a estar al final de la lista", lista_ver_ultimo(lista) == &dato2);

    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
    printf("\n");
}

static void prueba_iter_externo_remover_hasta_vaciar(void) {
    printf("INICIO DE PRUEBAS DE REMOVER CON ITERADOR EXTERNO\n");
    lista_t* lista = lista_crear();
    
    int dato1 = 0;
    int dato2 = 1;
    int dato3 = 2;

    lista_insertar_ultimo(lista, &dato1);
    lista_insertar_ultimo(lista, &dato2);
    lista_insertar_ultimo(lista, &dato3);

    print_test("se insertaron 3 elementos", lista_largo(lista) == 3);

    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("crear iterador", iter != NULL);

    print_test("el dato1 esta guardado al principio de la lista", lista_ver_primero(lista) == &dato1);
    print_test("el dato3 esta guardado al final de la lista", lista_ver_ultimo(lista) == &dato3);
    printf("Remuevo todos elemento en la posicion donde se crea el iterador\n");
    print_test("el dato1 fue removido correctamente", lista_iter_borrar(iter) == &dato1);
    print_test("el dato2 fue removido correctamente", lista_iter_borrar(iter) == &dato2);
    print_test("el dato3 fue removido correctamente", lista_iter_borrar(iter) == &dato3);
    print_test("la lista esta vacia", lista_esta_vacia(lista) == true);
    print_test("ver_primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("ver_ultimo es NULL", lista_ver_ultimo(lista) == NULL);

    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
    printf("\n");
}

static void prueba_iter_externo_insertar_medio(void) {
    printf("INICIO DE PRUEBAS DE INSERTAR Y REMOVER UN ELEMENTO DEL MEDIO CON ITERADOR EXTERNO\n");
    lista_t* lista = lista_crear();

    int dato1 = 0;
    int dato2 = 1;
    int dato3 = 2;
    int dato4 = 3;
    int dato5 = 4;
    int dato_extra = 5;

    lista_insertar_ultimo(lista, &dato1);
    lista_insertar_ultimo(lista, &dato2);
    lista_insertar_ultimo(lista, &dato3);
    lista_insertar_ultimo(lista, &dato4);
    lista_insertar_ultimo(lista, &dato5);
    
    print_test("se insertaron 5 elementos a la lista", lista_largo(lista) == 5);

    lista_iter_t *iter = lista_iter_crear(lista);
    int contador = 0;

    printf("Recorro la lista hasta la mitad\n");
    while (contador != lista_largo(lista)/2) {
        lista_iter_avanzar(iter);
        contador++;
    }

    print_test("el dato nuevo es insertado en el medio de la lista", lista_iter_insertar(iter, &dato_extra));
    print_test("la lista tiene 6 elementos", lista_largo(lista) == 6);
    print_test("el dato1 sigue estando primero", lista_ver_primero(lista) == &dato1);
    print_test("el dato5 sigue estando ultimo", lista_ver_ultimo(lista) == &dato5);
    print_test("el dato nuevo insertado esta en el medio", lista_iter_ver_actual(iter) == &dato_extra);
    print_test("el dato nuevo es removido del medio de la lista", lista_iter_borrar(iter) == &dato_extra);
    print_test("la lista tiene 5 elementos", lista_largo(lista) == 5);
    print_test("el dato1 sigue estando primero", lista_ver_primero(lista) == &dato1);
    print_test("el dato5 sigue estando ultimo", lista_ver_ultimo(lista) == &dato5);
    print_test("el dato removido ya no esta en el medio de la lista", lista_iter_ver_actual(iter) != &dato_extra);
    
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
    printf("\n");
}


// PRUEBAS DE ITERADOR INTERNO

bool sumar_todos(void* dato, void* suma) {
    *(int*) suma += *(int*) dato;
    return true;
}

static void prueba_iter_interno_funcionamiento_sin_condicion(void) {
    printf("INICIO DE PRUEBA DE FUNCIONAMIENTO DE ITERADOR INTERNO SIN CONDICION DE CORTE\n");
    lista_t* lista = lista_crear();

    int dato1 = 0;
    int dato2 = 1;
    int dato3 = 2;
    int dato4 = 3;
    int dato5 = 4;
    int suma = 0;

    lista_insertar_ultimo(lista, &dato1);
    lista_insertar_ultimo(lista, &dato2);
    lista_insertar_ultimo(lista, &dato3);
    lista_insertar_ultimo(lista, &dato4);
    lista_insertar_ultimo(lista, &dato5);

    printf("Itero hasta el final de la lista sumando los datos\n");
    lista_iterar(lista, sumar_todos, &suma);
    print_test("la suma de todos los elementos de la lista es 10", suma == 10);
    lista_destruir(lista, NULL);
    printf("\n");
}

bool sumar_hasta_3(void* dato, void* suma) {
    if (*(int*) dato == 3){
        return false;
    }
    *(int*) suma += *(int*) dato;
    return true;
}

static void prueba_iter_interno_funcionamiento_con_condicion(void) {
    printf("INICIO DE PRUEBA DE FUNCIONAMIENTO DE ITERADOR INTERNO CON CONDICION DE CORTE\n");
    lista_t* lista = lista_crear();
    int dato1 = 0;
    int dato2 = 1;
    int dato3 = 2;
    int dato4 = 3;
    int dato5 = 4;
    int suma = 0;

    lista_insertar_ultimo(lista, &dato1);
    lista_insertar_ultimo(lista, &dato2);
    lista_insertar_ultimo(lista, &dato3);
    lista_insertar_ultimo(lista, &dato4);
    lista_insertar_ultimo(lista, &dato5);

    printf("Itero sumando los datos hasta el dato que contiene el numnero 3\n");
    lista_iterar(lista, sumar_hasta_3, &suma);
    print_test("la suma de todos los elementos sumados es 3", suma == 3);
    lista_destruir(lista, NULL);
    printf("\n");
}

void pruebas_lista_estudiante() {
	prueba_lista_crear_destruir();
    prueba_lista_vacia();
    prueba_lista_insertar_distintos_tipos();
    prueba_lista_invariante();
    prueba_lista_volumen();
    prueba_lista_insertar_NULL();
    prueba_lista_borrar_hasta_vacia();
    prueba_lista_destruir_con_free();
    prueba_lista_destruir_pila();
    prueba_lista_destruccion_de_vacias();
    prueba_lista_destruccion_de_no_vacia_con_NULL();
    prueba_iter_externo_insertar();
    prueba_iter_externo_remover();
    prueba_iter_externo_remover_hasta_vaciar();
    prueba_iter_externo_insertar_medio();
    prueba_iter_interno_funcionamiento_sin_condicion();
    prueba_iter_interno_funcionamiento_con_condicion();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
