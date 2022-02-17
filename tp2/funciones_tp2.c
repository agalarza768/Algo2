#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funciones_tp2.h"
#include "heap.h"
#include "mensajes.h"
#include "cola.h"

//DEFINICION ESTRUCTURAS

struct lista_de_espera {
	cola_t *urgentes;
	heap_t *regulares;
	size_t cant_pacientes;
};

struct paciente {
	char *nombre;
	size_t anio_inscripcion;
};

struct doctor {
	char* nombre;
	char* especialidad;
	size_t pacientes_atendidos;
};


// FUNCIONES AUXILIARES

int cmp_antiguedad(paciente_t* const a, paciente_t* const b) {
	if (a->anio_inscripcion < b->anio_inscripcion) return 1;
	else if (a->anio_inscripcion > b->anio_inscripcion) return -1;
	else return 0;
}

// PRIMITIVAS DE DOCTOR

void* crear_doctor(char** campos, void* extra) {
	doctor_t* doctor = malloc(sizeof(doctor_t));

	if (!doctor) return NULL;

	doctor->nombre = strdup(campos[0]);
	doctor->especialidad = strdup(campos[1]);
	doctor->pacientes_atendidos = 0;

	return doctor;
}

char* doctor_obtener_nombre(doctor_t* doctor) {
	return doctor->nombre;
}

char* doctor_obtener_especialidad(doctor_t* doctor) {
	return doctor->especialidad;
}

void doctor_atender_paciente(doctor_t* doctor) {
	doctor->pacientes_atendidos++;
}

void doctor_imprimir(doctor_t* doctor, size_t n) {
	printf(INFORME_DOCTOR, n, doctor->nombre, doctor->especialidad, doctor->pacientes_atendidos);
}

void doctor_destruir(void* doctor) {
	doctor_t* doctor_a_destruir = doctor;
	free(doctor_a_destruir->nombre);
	free(doctor_a_destruir->especialidad);

	free(doctor);
}

// PRIMITIVA DE PACIENTE

void* crear_paciente(char** campos, void* extra) {
	paciente_t* paciente = malloc(sizeof(paciente_t));

	if (!paciente) return NULL;

	paciente->nombre = strdup(campos[0]);

	char* anio = campos[1];
	char* end;
	paciente->anio_inscripcion = strtol(anio, &end, 10);

	return paciente;
}

char* paciente_obtener_nombre(paciente_t* paciente) {
	return paciente->nombre;
}

void paciente_destruir(void* paciente) {
	paciente_t* paciente_a_destruir = paciente;
	free(paciente_a_destruir->nombre);

	free(paciente);
}

// PRIMITIVAS DE LISTA DE ESPERA

void* lista_de_espera_crear(char *especialidad) {
	lista_de_espera_t *lista_de_espera = malloc(sizeof(lista_de_espera_t));
	if (!lista_de_espera) return NULL;
	
	lista_de_espera->urgentes = cola_crear();
	if(!lista_de_espera->urgentes) return NULL; 

	lista_de_espera->regulares = heap_crear((cmp_func_t)cmp_antiguedad);
	if(!lista_de_espera->regulares) return NULL;

	lista_de_espera->cant_pacientes = 0;
	return lista_de_espera;
}

bool lista_de_espera_encolar(lista_de_espera_t *lista_de_espera, paciente_t *paciente, const char* urgencia) {
	if (strcmp(urgencia, "URGENTE") == 0) {
		if(!cola_encolar(lista_de_espera->urgentes, paciente)) return false;
	} else {
		if(!heap_encolar(lista_de_espera->regulares, paciente)) return false;
	}
	lista_de_espera->cant_pacientes++;

	return true;
}

paciente_t* lista_de_espera_desencolar(lista_de_espera_t *lista_de_espera, const char* nombre_doctor) {
	paciente_t* paciente;
	if (!cola_esta_vacia(lista_de_espera->urgentes)) {
		paciente = cola_desencolar(lista_de_espera->urgentes);
	} else {
		paciente = heap_desencolar(lista_de_espera->regulares);
	}

	if (!paciente) return NULL;

	lista_de_espera->cant_pacientes--;
	return paciente;
}

size_t lista_de_espera_cant_pacientes(lista_de_espera_t *lista_de_espera) {
	return lista_de_espera->cant_pacientes;
}

void lista_de_espera_destruir(void* lista_de_espera) {
	lista_de_espera_t* lista_a_destruir = lista_de_espera;
	cola_destruir(lista_a_destruir->urgentes, NULL);
	heap_destruir(lista_a_destruir->regulares, NULL);

	free(lista_de_espera);
}
