/*
 * estado.h - Variables globales del sistema (los dos mapas hash y los contadores de ID).
 * ARCHIVO COMPLETO.
 */
#ifndef ESTADO_H
#define ESTADO_H

#include "tipos.h"

extern Usuario  *mapaUsuarios[TAM_MAPA];    /* cada posicion = una cubeta (lista encadenada) */
extern Proyecto *mapaProyectos[TAM_MAPA];
extern int siguienteIdUsuario;
extern int siguienteIdProyecto;

#endif
