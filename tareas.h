/* tareas.h - Lista enlazada de tareas de un proyecto. Responsable: INTEGRANTE 5 */
#ifndef TAREAS_H
#define TAREAS_H

#include "tipos.h"

/* Busca una tarea por ID dentro del proyecto. Devuelve NULL si no existe. */
Tarea *buscarTarea(const Proyecto *p, int id);

/* Crea una tarea (estado POR_HACER, sin responsable) y la inserta al inicio de la lista. */
Tarea *crearTarea(Proyecto *p, const char *nombre, const char *descripcion, int prioridad);

/* Desenlaza y libera la tarea. Devuelve 1 si existia, 0 si no. */
int eliminarTarea(Proyecto *p, int id);

/* Asigna la tarea al usuario con ese username, validando que pertenezca al proyecto.
 * Devuelve 0 si ok, 1 si el usuario no existe, 2 si no es integrante del proyecto. */
int asignarTarea(Proyecto *p, Tarea *t, const char *username);

/* Cambia el estado de la tarea. Devuelve 0 si ok, 1 si el estado no es valido (1..3). */
int cambiarEstado(Tarea *t, int nuevoEstado);

#endif
