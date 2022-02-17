#ifndef LISTA_DE_ESPERA_H
#define LISTA_DE_ESPERA_H

#include <stdbool.h>  // bool
#include <stddef.h>   // size_t

#include "abb.h"
#include "hash.h"
#include "csv.h"

typedef struct clinica clinica_t;

/* Constructor de la clinica. Recibe como parametro las rutas de los archivos de la lista de doctores 
y la lista de pacientes.  Devuelve NULL en caso de error. */
clinica_t* clinica_crear(const char* ruta_doctores, const char* ruta_pacientes);

/* Recibe el nombre de una especialidad y devuelve true si existe en la clinica, false en caso contrario. */
bool clinica_existe_especialidad(clinica_t* clinica, const char* nombre_especialidad);

/* Recibe el nombre de un doctor y devuelve true si existe en la clinica, false en caso contrario. */
bool clinica_existe_doctor(clinica_t* clinica, const char* nombre_doctor);

/* Recibe el nombre de un paciente y devuelve true si esta inscriptos en la clinica, false en caso contrario. */
bool clinica_existe_paciente(clinica_t* clinica, const char* nombre_paciente);

/* Recibe el nombre de un paciente, el nombre de una especialidad y agrega al paciente a la lista de espera de esa especialidad. */
void clinica_pedir_turno(clinica_t* clinica, const char* nombre_paciente, const char* nombre_especialidad, const char* urgencia);

/* Recibe el nombre de un doctor, y se atiende al primer paciente ingresado en la cola de urgentes. 
En caso de estar vacia, se atiente al paciente de mayor antiguedad ingresado en la cola de regulares */
void clinica_atender_paciente(clinica_t* clinica, const char* nombre_doctor);

/* Recibe dos nombres de doctores e imprime por pantalla una lista de doctores en orden alfabetico 
junto a la cantidad de pacientes atendidos por cada uno, comenzando desde el primer nombre hasta el 
segundo nombre. Si el nombre de inicio o de fin es NULL, entonces la lista comenzara desde el inicio 
o seguira hasta el final de la lista completa respectivamente. */
void clinica_informe_doctores(clinica_t* clinica, const char *desde,  const char *hasta);

/* Elimina la clinica. */
void clinica_destruir(clinica_t* clinica);

#endif
