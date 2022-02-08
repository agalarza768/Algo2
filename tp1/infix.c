#include "calc_helper.h"
#include "strutil.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void infix(char **arreglo_palabras) {
    pila_t* pila = pila_crear();
    
    struct calc_token tok;
    for (int i = 0; arreglo_palabras[i] != NULL; i++){
        if (!calc_parse(arreglo_palabras[i], &tok)) {
            printf("ERROR\n");
            pila_destruir(pila);
			free_strv(arreglo_palabras);
            return;
        }
        else if (tok.type == TOK_NUM) {
            printf("%s ", arreglo_palabras[i]);
        }
        else if (tok.type == TOK_OPER) {
			while(!pila_esta_vacia(pila)) {
				char *tope = pila_ver_tope(pila);
                struct calc_token tok_tope;
                calc_parse(tope, &tok_tope);
                if (tok_tope.type == TOK_OPER && (tok_tope.oper.precedencia > tok.oper.precedencia || (tok_tope.oper.precedencia == tok.oper.precedencia && tok.oper.asociatividad == ASSOC_LEFT)) && tok.type != TOK_LPAREN){
					char* elemento = pila_desapilar(pila);
                    printf("%s ", elemento);
				} else {
					break;
				}
			}
			pila_apilar(pila, arreglo_palabras[i]);
        }
        else if (tok.type == TOK_LPAREN) {
            pila_apilar(pila, arreglo_palabras[i]);
		}
		else if (tok.type == TOK_RPAREN) {
			while(!pila_esta_vacia(pila)) {
				char *tope = pila_ver_tope(pila);
                struct calc_token tok_tope;
                calc_parse(tope, &tok_tope);
                if(tok_tope.type != TOK_LPAREN){
					char* elemento = pila_desapilar(pila);
                    printf("%s ", elemento);
				} else {
					pila_desapilar(pila);
                    break;
				}
			}
		}
	}
	while(!pila_esta_vacia(pila)){
        char* elemento = pila_desapilar(pila);
        printf("%s ", elemento);
    }
    pila_destruir(pila);
    printf("\n");
}

int main(int argc, const char *argv[]) {
    if (argc != 1) {
        return 1;
    }

    char* linea = NULL;
    size_t tam = 0;
    ssize_t leidos;

    while((leidos = getline(&linea, &tam, stdin)) != EOF) {
        char **strv = infix_split(linea);
        infix(strv);
        free_strv(strv);
    }
    free(linea);

    return 0;
}

