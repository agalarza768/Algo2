#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funciones_tp2.h"
#include "heap.h"
#include "mensajes.h"
#include "cola.h"
#include "clinica.h"

struct clinica {
	hash_t* especialidades;
	abb_t* doctores;
	hash_t* pacientes;
};

// FUNCIONES AUXILIARES

bool incluir_doctor(const char *clave, void *dato, void *extra) {
	doctor_t* doctor = dato;
	lista_t* informe = extra;
	
	lista_insertar_ultimo(informe, doctor);
	
	return true;
}

// PRIMITIVAS DE CLINICA

clinica_t* clinica_crear(const char* ruta_doctores, const char* ruta_pacientes) {
	lista_t* lista_doctores = csv_crear_estructura(ruta_doctores, crear_doctor, NULL);

	if (!lista_doctores) {
		printf(ENOENT_ARCHIVO, "doctores");
		return NULL;
	}

	lista_t* lista_pacientes = csv_crear_estructura(ruta_pacientes, crear_paciente, NULL);

	if (!lista_pacientes) {
		printf(ENOENT_ARCHIVO, "pacientes");
		lista_destruir(lista_doctores, doctor_destruir);
		return NULL;
	}

	clinica_t* clinica = malloc(sizeof(clinica_t));

	if (!clinica) {
		lista_destruir(lista_doctores, doctor_destruir);
		lista_destruir(lista_pacientes, paciente_destruir);
		return NULL;
	}

	clinica->especialidades = hash_crear(lista_de_espera_destruir);
	if (!clinica->especialidades) {
		lista_destruir(lista_doctores, doctor_destruir);
		lista_destruir(lista_pacientes, paciente_destruir);
		free(clinica);
		return NULL;
	}

	clinica->doctores = abb_crear(strcmp, doctor_destruir);

	if (!clinica->doctores) {
		lista_destruir(lista_doctores, doctor_destruir);
		lista_destruir(lista_pacientes, paciente_destruir);
		hash_destruir(clinica->especialidades);
		free(clinica);
		return NULL;
	}

	clinica->pacientes = hash_crear(paciente_destruir);

	if (!clinica->pacientes) {
		lista_destruir(lista_doctores, doctor_destruir);
		lista_destruir(lista_pacientes, paciente_destruir);
		hash_destruir(clinica->especialidades);
		abb_destruir(clinica->doctores);
		free(clinica);
		return NULL;
	}

	while(!lista_esta_vacia(lista_doctores)) {
		doctor_t* doctor = lista_borrar_primero(lista_doctores);
		abb_guardar(clinica->doctores, doctor_obtener_nombre(doctor), doctor);
		char* especialidad = doctor_obtener_especialidad(doctor);

		if (!hash_pertenece(clinica->especialidades, especialidad)) {
			hash_guardar(clinica->especialidades, especialidad, lista_de_espera_crear(especialidad));
		}
	}
	lista_destruir(lista_doctores, NULL);

	while (!lista_esta_vacia(lista_pacientes)) {
		paciente_t* paciente = lista_borrar_primero(lista_pacientes);
		hash_guardar(clinica->pacientes, paciente_obtener_nombre(paciente), paciente);
	}
	lista_destruir(lista_pacientes, NULL);
	
	return clinica;
}

bool clinica_existe_especialidad(clinica_t* clinica, const char* nombre_especialidad) {
	return hash_pertenece(clinica->especialidades, nombre_especialidad);
}

bool clinica_existe_doctor(clinica_t* clinica, const char* nombre_doctor) {
	return abb_pertenece(clinica->doctores, nombre_doctor);
}

bool clinica_existe_paciente(clinica_t* clinica, const char* nombre_paciente) {
	return hash_pertenece(clinica->pacientes, nombre_paciente);
}

void clinica_pedir_turno(clinica_t* clinica, const char* nombre_paciente, const char* nombre_especialidad, const char* urgencia) {
	lista_de_espera_t* lista_de_espera = hash_obtener(clinica->especialidades, nombre_especialidad);
	paciente_t* paciente = hash_obtener(clinica->pacientes, nombre_paciente);
	
	if(!lista_de_espera_encolar(lista_de_espera, paciente, urgencia)) return;

	printf(PACIENTE_ENCOLADO, nombre_paciente);
	printf(CANT_PACIENTES_ENCOLADOS, lista_de_espera_cant_pacientes(lista_de_espera), nombre_especialidad);
}

void clinica_atender_paciente(clinica_t* clinica, const char* nombre_doctor) {
	doctor_t* doctor = abb_obtener(clinica->doctores, nombre_doctor);
	char *nombre_especialidad = doctor_obtener_especialidad(doctor);
	lista_de_espera_t* lista_de_espera = hash_obtener(clinica->especialidades, nombre_especialidad);

	paciente_t* paciente_atendido = lista_de_espera_desencolar(lista_de_espera, nombre_doctor);

	if (!paciente_atendido) {
		printf(SIN_PACIENTES);
		return;
	}

	doctor_atender_paciente(doctor);

	printf(PACIENTE_ATENDIDO, paciente_obtener_nombre(paciente_atendido));
	printf(CANT_PACIENTES_ENCOLADOS, lista_de_espera_cant_pacientes(lista_de_espera), nombre_especialidad);
}

void clinica_informe_doctores(clinica_t* clinica, const char *desde,  const char *hasta) {
	lista_t* informe = lista_crear();
	abb_in_order(clinica->doctores, incluir_doctor, informe, desde, hasta);
	
	size_t cant_doctores = lista_largo(informe);
	printf(DOCTORES_SISTEMA, cant_doctores);
	
	for (size_t i = 0; i < cant_doctores; i++) {
		doctor_t* doctor = lista_borrar_primero(informe);
		doctor_imprimir(doctor, i+1);
	}
	
	lista_destruir(informe, NULL);
}

void clinica_destruir(clinica_t* clinica) {
	hash_destruir(clinica->especialidades);
	abb_destruir(clinica->doctores);
	hash_destruir(clinica->pacientes);
	free(clinica);
}
