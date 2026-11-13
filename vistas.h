/* vistas.h - Tablero Kanban y listados. Responsable: INTEGRANTE 6 */
#ifndef VISTAS_H
#define VISTAS_H

#include "tipos.h"

/* Muestra una tarea en una linea: ID, nombre, prioridad y responsable. */
void imprimirTarea(const Tarea *t);

/* Tablero Kanban: las tareas del proyecto agrupadas en POR HACER / EN PROGRESO / TERMINADA. */
void mostrarTablero(const Proyecto *p);

/* Tareas asignadas al usuario en todos los proyectos donde participa. */
void tareasAsignadas(const Usuario *u);

#endif
