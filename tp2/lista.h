#include <stddef.h>
#include <stdbool.h>

// DEFINICION DE TIPOS DE DATOS

struct pila;
typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;


// PRIMITIVAS DE LA LISTA

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve true si la lista no tiene elementos enlistados, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento a la lista en la primera posición. Devuelve falso en caso de error.
// Pre: la cola fue creada.
// Post: se agregó un nuevo elemento a la cola, valor se encuentra al principio
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento a la lista en la ultima posición. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del último elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el último elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Devuelve la cantidad de elementos que contiene la lista.
// Pre: la lista fue creada.
// Post: se devolvió el valor de la cantidad de elementos de la lista.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));


// PRIMITIVA DEL ITERADOR INTERNO

// Itera la lista. Lo que devuelva la función visitar determina la condición de corte,
// si devuelve true entonces se continúa iterando mientras que si devuelve false se cumple
// la condicion de corte y se detiene la iteración.
// Pre: la lista fue creada, visitar determina la condición de corte
// Post: se iteró la lista hasta que la condición de corte determinada por visitar se cumplió
// o hasta que llegó al final de la lista.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


// PRIMITIVAS DEL ITERADOR EXTERNO

// Crea un iterador de lista.
// Pre: la lista fue creada
// Post: devuelve una nuevo iterador de lista.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza una posición en la lista. Devuelve false en caso de que no pueda avanzar mas.
// Pre: el iterador fue creado.
// Post: el iterador avanzo una posición en la lista.
bool lista_iter_avanzar(lista_iter_t *iter);

// Obtiene el valor del elemento en la posicion actual del iterador en la lista. 
// Si la posición actual está vacía devuelve NULL.
// Pre: el iterador fue creado.
// Post: se devolvió el elemento de la posicion actual del iterador en la lista, 
// cuando no está vacía y no se encuentre en el final.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve true si el iterador se encuentra en el final de la lista, false en caso contrario.
// Pre: el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
// Post: se eliminó el iterador.
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un nuevo elemento a la lista en la posicion en la que se encuentra el iterador actualmente. 
// Devuelve falso en caso de error.
// Pre: el iterador fue creado.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra en la posicon de la lista en la
// que se encuentra el iterador actualmente
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Saca un elemento de la lista en la posicion en la que se encuentra el iterador actualmente. 
// Si la lista está vacía, devuelve NULL.
// Pre: el iterador fue creado.
// Post: se devolvió el valor del elemento en la posicion actual del iterador, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_iter_borrar(lista_iter_t *iter);
