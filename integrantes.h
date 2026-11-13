/* integrantes.h - Relacion usuario <-> proyecto (listas cruzadas). Responsable: INTEGRANTE 4 */
#ifndef INTEGRANTES_H
#define INTEGRANTES_H

#include "tipos.h"

/* 1 si el usuario pertenece al proyecto, 0 si no. */
int esIntegrante(const Proyecto *p, const Usuario *u);

/* Agrega al usuario al proyecto creando DOS nodos (uno en cada lista).
 * Devuelve 0 si ok, 1 si ya era integrante, -1 si falta memoria. */
int agregarIntegrante(Proyecto *p, Usuario *u);

/* Quita al usuario del proyecto (ambas listas) y deja sin responsable sus tareas.
 * Devuelve 0 si ok, 1 si no era integrante, 2 si es el creador (no se puede eliminar). */
int eliminarIntegrante(Proyecto *p, Usuario *u);

/* Muestra los integrantes de un proyecto, indicando cual es el creador. */
void listarIntegrantes(const Proyecto *p);

/* Submenu: ver / agregar / eliminar integrantes. */
void menuIntegrantes(Proyecto *p);

#endif
