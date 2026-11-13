/* estado.c - Definicion de las variables globales. ARCHIVO COMPLETO. */
#include "estado.h"

Usuario  *mapaUsuarios[TAM_MAPA];     /* se inicializan en NULL automaticamente */
Proyecto *mapaProyectos[TAM_MAPA];
int siguienteIdUsuario  = 1;
int siguienteIdProyecto = 1;
