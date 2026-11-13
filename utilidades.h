/*
 * utilidades.h - Funciones de apoyo para leer datos y mostrar textos.
 * ARCHIVO COMPLETO: usalas en tus funciones, no hace falta modificarlas.
 */
#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <stddef.h>
#include "tipos.h"

/* Muestra msg y lee una linea (sin el salto de linea). Devuelve 0 si se cierra la entrada. */
int leerLinea(const char *msg, char *buf, size_t n);

/* Muestra msg y lee un entero. Devuelve -1 si lo escrito no es un numero (y 0 si se cierra la entrada). */
int leerEntero(const char *msg);

/* 1 si el texto esta vacio */
int vacio(const char *s);

const char *textoEstado(Estado e);      /* "POR HACER", "EN PROGRESO", "TERMINADA" */
const char *textoPrioridad(int p);      /* "Baja", "Media", "Alta" */

/* Aviso uniforme para las funciones que aun no estan implementadas. */
void noImplementado(const char *funcion);

#endif
