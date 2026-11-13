/*
 * tareas.c - Operaciones sobre la lista enlazada de tareas de un proyecto.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tareas.h"
#include "usuarios.h"
#include "integrantes.h"

Tarea *buscarTarea(const Proyecto *p, int id) {
    Tarea *t = p->tareas;
    while (t && t->id != id) t = t->sig;
    return t;
}

Tarea *crearTarea(Proyecto *p, const char *nombre, const char *descripcion, int prioridad) {
    Tarea *t = malloc(sizeof *t);
    if (!t) return NULL;
    t->id = p->siguienteIdTarea++;
    snprintf(t->nombre, sizeof t->nombre, "%s", nombre);
    snprintf(t->descripcion, sizeof t->descripcion, "%s", descripcion);
    t->prioridad = prioridad;
    t->estado = POR_HACER;                                    /* estado inicial */
    t->idResponsable = 0;
    t->sig = p->tareas;                                       /* insercion al inicio */
    p->tareas = t;
    return t;
}

int eliminarTarea(Proyecto *p, int id) {
    Tarea *ant = NULL, *t = p->tareas;
    while (t && t->id != id) { ant = t; t = t->sig; }
    if (!t) return 0;
    if (ant) ant->sig = t->sig; else p->tareas = t->sig;      /* desenlazar */
    free(t);
    return 1;
}

int asignarTarea(Proyecto *p, Tarea *t, const char *username) {
    Usuario *u = buscarUsuario(username);
    if (!u) return 1;                                         /* usuario inexistente */
    if (!esIntegrante(p, u)) return 2;                        /* no pertenece al proyecto */
    t->idResponsable = u->id;
    return 0;
}

int cambiarEstado(Tarea *t, int nuevoEstado) {
    if (nuevoEstado < POR_HACER || nuevoEstado > TERMINADA) return 1;
    t->estado = (Estado)nuevoEstado;
    return 0;
}
