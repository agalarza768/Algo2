#include <stdlib.h>
#include "strutil.h"
#include "string.h"

#include <stdio.h>

#define _POSIX_C_SOURCE 200809L

char *substr(const char *str, size_t n) {
    return strndup(str, n);
}

char **split(const char *str, char sep) {
    size_t largo = strlen(str);
    size_t cant_separaciones = 0;

    for (int i = 0; i < largo; i++) {
        if (str[i] == sep) {
            cant_separaciones++;
        }
    }
    cant_separaciones++;

    char **separado = calloc(cant_separaciones + 1, sizeof(char *));  

    if (separado == NULL) return NULL;

    size_t cadenas_separadas = 0;
    size_t comienzo_cadena = 0;
    size_t caracteres_a_copiar = 0;
    
    for (int i = 0; i <= largo; i++) {
        if (str[i] == sep || str[i] == '\0') {
            if (i-1 < 0 || str[i-1] == sep) {
                char* nueva_cadena = malloc(sizeof(char));

                if (nueva_cadena == NULL) return NULL;

                *nueva_cadena = '\0';
                separado[cadenas_separadas] = nueva_cadena;
            } else {
                char* nueva_cadena = strndup(str + comienzo_cadena, caracteres_a_copiar);
                if (nueva_cadena == NULL) return NULL;

                separado[cadenas_separadas] = nueva_cadena;
            }
            comienzo_cadena = i + 1;
            cadenas_separadas++;
            caracteres_a_copiar = 0;
            continue;
        }
        caracteres_a_copiar++;
    }
    return separado;
}

char *join(char **strv, char sep) {
    size_t largo = 0;
    for (int i = 0; strv[i] != NULL; i++) {
        largo += strlen(strv[i]) + 1;
    }
    char* resultado = malloc(sizeof(char) * largo+1);
    if (resultado == NULL) return NULL;
    
    if (strv[0] == NULL) {
		resultado[0] = '\0';
		return resultado;
	}
    
    char* puntero_a_final;
    
    for (int i = 0; strv[i] != NULL; i++) {
		largo = strlen(strv[i]);
        char* cadena_copiada = malloc(sizeof(char)*(largo+2));
        if (cadena_copiada == NULL) return NULL;
        strcpy(cadena_copiada, strv[i]);
        
        if (strv[i+1] != NULL || sep == '\n') {
            cadena_copiada[largo] = sep;
            cadena_copiada[largo+1] = '\0';
        }

        if (i == 0) {
			puntero_a_final = stpcpy(resultado, cadena_copiada);
		} else {
            puntero_a_final = stpcpy(puntero_a_final, cadena_copiada);
        }
        free(cadena_copiada);
    }
    return resultado;
}

void free_strv(char *strv[]) {
    for (int i = 0; strv[i] != NULL; i++){
		if(strv[i] != NULL) {
			free(strv[i]);
		}
    }
    free(strv);
}
