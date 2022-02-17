#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutil.h"
#include "mensajes.h"
#include "clinica.h"

#define COMANDO_PEDIR_TURNO "PEDIR_TURNO"
#define COMANDO_ATENDER "ATENDER_SIGUIENTE"
#define COMANDO_INFORME "INFORME"

size_t cant_parametros(const char** parametros) {
	size_t contador = 0;
	while (parametros[contador] != NULL) {
		contador++;
	}
	return contador;
}

void procesar_comando(const char* comando, const char** parametros, clinica_t* clinica) {
	if (strcmp(comando, COMANDO_PEDIR_TURNO) == 0) {
		if (cant_parametros(parametros) < 3) {
			printf(ENOENT_PARAMS, comando);
			return;
		}
		if (!clinica_existe_paciente(clinica, parametros[0])) {
			printf(ENOENT_PACIENTE, parametros[0]);
		} else if (!clinica_existe_especialidad(clinica, parametros[1])) {
			printf(ENOENT_ESPECIALIDAD, parametros[1]);
		} else if (strcmp(parametros[2], "URGENTE") != 0 && strcmp(parametros[2], "REGULAR") != 0) {
			printf(ENOENT_URGENCIA, parametros[2]);
		} else {
			clinica_pedir_turno(clinica, parametros[0], parametros[1], parametros[2]);
		}

	} else if (strcmp(comando, COMANDO_ATENDER) == 0) {
		if (cant_parametros(parametros) < 1) {
			printf(ENOENT_PARAMS, comando);
			return;
		} else if (!clinica_existe_doctor(clinica, parametros[0])) {
			printf(ENOENT_DOCTOR, parametros[0]);
			return;
		}
		clinica_atender_paciente(clinica, parametros[0]);

	} else if (strcmp(comando, COMANDO_INFORME) == 0) {
		if (cant_parametros(parametros) < 2) {
			printf(ENOENT_PARAMS, comando);
			return;
		}
		clinica_informe_doctores(clinica, parametros[0], parametros[1]);
	} else {
		printf(ENOENT_CMD, comando);
	}
}

void eliminar_fin_linea(char* linea) {
	size_t len = strlen(linea);
	if (linea[len - 1] == '\n') {
		linea[len - 1] = '\0';
	}
}

void procesar_entrada(clinica_t* clinica) {
	char* linea = NULL;
	size_t c = 0;
	while (getline(&linea, &c, stdin) > 0) {
		eliminar_fin_linea(linea);
		char** campos = split(linea, ':');
		if (campos[1] == NULL) {
			printf(ENOENT_FORMATO, linea);
			free_strv(campos);
			continue;	
		}
		char** parametros = split(campos[1], ',');
		procesar_comando(campos[0], (const char**)parametros, clinica);
		free_strv(parametros);
		free_strv(campos);
	}
	free(linea);
}

int main(int argc, char **argv) {
	if (argc < 3) {
		printf(ENOENT_CANT_PARAMS);
		return 1;
	}
	
	clinica_t* clinica = clinica_crear(argv[1], argv[2]);

	if (!clinica) return 1;

	procesar_entrada(clinica);

	clinica_destruir(clinica);
	return 0;
}
