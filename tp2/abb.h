#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stddef.h>

/* Tipos de función para comparar claves y destruir datos. */
typedef int (*abb_comparar_clave_t)(const char *, const char *);
typedef void (*abb_destruir_dato_t)(void *);

/* Los structs deben llamarse 'abb' y 'abb_iter'. */

typedef struct abb abb_t;
typedef struct abb_iter abb_iter_t;


// PRIMITIVAS DEL ARBOL BINARIO DE BUSQUEDA

/*Crea un arbol binario de busqueda.
 *Pre:La funcion cmp es una funcion que compara los datos del arbol, la funcion destruir_dato
 *es capaz de destruir los datos guardados, o NULL en caso de no utilizarla.
 *Post:Se creo un arbol binario de busqueda vacio
 */
abb_t *abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/*Guarda una clave en el arbol, si la clave ya se encuentra en la estructura, reemplaza el dato,
 *de no poder guardarlo devuelve false.
 *Pre:La estructura abb fue creada.
 *Post:Se almaceno el par (clave,dato) en el arbol.
 */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

/*Borra la clave del abb y devuelve el dato asociado. Devuelve NULL si el dato no estaba.
 *Pre:La estructura abb fue creada.
 *Post:Se borro el par (clave,dato) del arbol y se devolvio el dato en caso de encontrarse.
 */
void *abb_borrar(abb_t *arbol, const char *clave);

/*Obtiene el valor asociado a una clave, si la clave no se encuentra devuelve NULL.
 *Pre: La estructura abb fue creada.
 *Post:Se devolvio el dato asociado en caso de encontrar la clave, caso contrario devuelve NULL.
 */
void *abb_obtener(const abb_t *arbol, const char *clave);

/*Determina si la clave pertenece o no al abb.
 *Pre:La estructura abb fue creada.
 *Post:En caso de encontrar la clave, se devuelve true, caso contrario false.
 */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/*Devuelve la cantdad de elementos en el abb.
 *Pre:La estructura abb fue creada..
 */
size_t abb_cantidad(abb_t *arbol);

/*Destruye el abb liberando la memoria pedida y llamando a la funcion destruir para cada (clave,dato).
 *Pre:La estructura abb fue creada.
 *Post:La estructura abb fue destruida.
 */
void abb_destruir(abb_t *arbol);

/* Recorre el abb en orden de menor a mayor, para cada par (clave,dato) llama a la funcion visitar
 * esta funcion devuelve true si se quiere seguir iterando, false en caso contrario.
 * No puede agregar ni quitar elementos.
 * Pre:La estructura abb fue creada.
 * Post:Se llamo a la funcion para cada par (clave,valor) hasta que devuelva false.
 */
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra, const char *desde,  const char *hasta);

// PRIMITIVAS DEL ITERADOR EXTERNO DEL ABB

/*Crea el iterador del abb*/
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

/*Avanza el iterador*/
bool abb_iter_in_avanzar(abb_iter_t *iter);

/*Devuelve clave actual, esa clave no se puede modificar ni liberar*/
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

/*Comprueba si el iterador llego al final*/
bool abb_iter_in_al_final(const abb_iter_t *iter);

/*Destruye el iterador*/
void abb_iter_in_destruir(abb_iter_t *iter);

#endif  // ABB_H
