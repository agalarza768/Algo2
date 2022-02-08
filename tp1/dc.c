#include <stdlib.h>
#include <stdio.h>
#include "calc_helper.h"
#include "strutil.h"
#include <math.h>
#include <string.h>

void calculadora(char **arreglo_palabras) {
    pilanum_t* pila = pilanum_crear();
    bool error_encontrado = false;
    struct calc_token tok;
    int operandos = 0;
    calc_num resultado = 0;
	
	for (int i = 0; arreglo_palabras[i] != NULL; i++){
        if (!calc_parse(arreglo_palabras[i], &tok)) {
            error_encontrado = true;
            break;
        }
        else if (tok.type == TOK_NUM) {
            calc_num num = tok.value;
            apilar_num(pila, num);
            operandos++;
        }
        else if (tok.type == TOK_OPER) {
            if (operandos < tok.oper.num_operandos) {
                error_encontrado = true;
				break;
            }
            calc_num operando1;
            calc_num operando2;
            calc_num operando3;
            
            desapilar_num(pila, &operando1);

			if (tok.oper.num_operandos > 1) {
				desapilar_num(pila, &operando2);
				if (tok.oper.num_operandos == 3) {
					desapilar_num(pila, &operando3);
				}
			}
			
			if (tok.oper.op == OP_ADD) {
				resultado = operando2 + operando1;
			}

			if (tok.oper.op == OP_SUB) {
				resultado = operando2 - operando1;
			}

			if (tok.oper.op == OP_MUL) {
				resultado = operando2 * operando1;
			}

			if (tok.oper.op == OP_DIV) {
				if (operando1 == 0) {
					error_encontrado = true;
					break;
				}
				resultado = operando2 / operando1;
			}

			if (tok.oper.op == OP_POW) {
				if (operando1 < 0) {
					error_encontrado = true;
					break;
				}
				resultado = pow(operando2, operando1);
			}

			if (tok.oper.op == OP_LOG) {
				if (operando1 < 2) {
					error_encontrado = true;
					break;
				}
				resultado = log(operando2) / log(operando1);
			}

			if (tok.oper.op == OP_RAIZ) {
				if (operando1 < 0) {
					error_encontrado = true;
					break;
				}
				resultado = sqrt(operando1);
			}

			if (tok.oper.op == OP_TERN) {
				if (!operando3) {
					resultado = operando1;
				}
				else {
					resultado = operando2;
				}
				operandos -= 2;
			}
			if (tok.oper.num_operandos != 1 && tok.oper.num_operandos != 3) {
				operandos--;
			}
			apilar_num(pila, resultado);
		}
	}
	calc_num resultado_final;
    desapilar_num(pila, &resultado_final);
	
	if (error_encontrado || !pila_esta_vacia(pila)) {
		printf("ERROR\n");
	}
	else {
		printf("%li\n", resultado_final);
	}
	
	pilanum_destruir(pila);
}

int main(int argc, const char *argv[]) {
    if (argc != 1) {
        return 1;
    }

    char* linea = NULL;
    size_t tam = 0;
	ssize_t leidos;

    while((leidos = getline(&linea, &tam, stdin)) != EOF) {
        char **strv = dc_split(linea);
        calculadora(strv);
        free_strv(strv);
    }
    free(linea);

    return 0;
}
