#include <stdbool.h>  // bool
#include <stddef.h>   // size_t

typedef struct lista_de_espera lista_de_espera_t;

typedef struct paciente paciente_t;

typedef struct doctor doctor_t;

// PRIMITIVAS DE DOCTOR

/* Constructor del doctor.*/
void* crear_doctor(char** campos, void* extra);

/* Devuelve el nombre del doctor recibido. */
char* doctor_obtener_nombre(doctor_t* doctor);

/* Devuelve la especialidad del doctor recibido. */
char* doctor_obtener_especialidad(doctor_t* doctor);

/* Se recibe el doctor que atendera un paciente, y se suma en uno a la cantidad de pacientes atendidos. */
void doctor_atender_paciente(doctor_t* doctor);

/* Se recibe un doctor e imprime por pantalla sus datos. */
void doctor_imprimir(doctor_t* doctor, size_t n);

/* Elimina el doctor. */
void doctor_destruir(void* doctor);

// PRIMITIVAS DE PACIENTE

/* Constructor del paciente. */
void* crear_paciente(char** campos, void* extra);

/* Devuelve el nombre del paciente recibido. */
char* paciente_obtener_nombre(paciente_t* paciente);

/* Elimina el paciente. */
void paciente_destruir(void* paciente);

// PRIMITIVA DE LISTA DE ESPERAS

/* Constructor de la lista de espera. */
void* lista_de_espera_crear(char *especialidad);

/* Recibe una lista de espera, un paciente y su respectiva urgencia, y encola al paciente en la lista segun el tipo de urgencia. */
bool lista_de_espera_encolar(lista_de_espera_t *lista_de_espera, paciente_t *paciente, const char* urgencia);

/* Recibe una lista de espera, el nombre de un doctor y desencola el paciente de la lista de espera de la respectiva especialidad del doctor. */
paciente_t* lista_de_espera_desencolar(lista_de_espera_t *lista_de_espera, const char* nombre_doctor);

/* Devuelve la cantidad de pacientes encolados en la lista de espera recibida. */
size_t lista_de_espera_cant_pacientes(lista_de_espera_t *lista_de_espera);

/* Elimina la lista de espera. */
void lista_de_espera_destruir(void* lista_de_espera);
