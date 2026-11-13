/*
 * vistas.c - Tablero Kanban y listados.
 */
#include <stdio.h>
#include <string.h>
#include "vistas.h"
#include "usuarios.h"
#include "utilidades.h"

void imprimirTarea(const Tarea *t) {
    char resp[LARGO_NOM + 4] = "sin asignar";
    if (t->idResponsable) {
        Usuario *u = buscarUsuarioPorId(t->idResponsable);
        if (u) snprintf(resp, sizeof resp, "%s", u->username);
    }
    printf("   [T-%02d] %-24s Prioridad: %-5s Responsable: %s\n",
           t->id, t->nombre, textoPrioridad(t->prioridad), resp);
}

void mostrarTablero(const Proyecto *p) {
    printf("\n=== TABLERO: %s (ID %d) ===\n", p->nombre, p->id);
    for (Estado e = POR_HACER; e <= TERMINADA; e++) {
        printf("\n -- %s --\n", textoEstado(e));
        int hay = 0;
        for (Tarea *t = p->tareas; t; t = t->sig) {
            if (t->estado == e) { imprimirTarea(t); hay = 1; }
        }
        if (!hay) printf("   (sin tareas)\n");
    }
    printf("\n");
}

void tareasAsignadas(const Usuario *u) {
    printf("\n=== TAREAS ASIGNADAS A %s ===\n", u->username);
    int hay = 0;
    for (NodoProyecto *n = u->proyectos; n; n = n->sig)
        for (Tarea *t = n->proyecto->tareas; t; t = t->sig)
            if (t->idResponsable == u->id) {
                printf("   [%s | T-%02d] %-24s %-11s Prioridad: %s\n",
                       n->proyecto->nombre, t->id, t->nombre,
                       textoEstado(t->estado), textoPrioridad(t->prioridad));
                hay = 1;
            }
    if (!hay) printf("   (no tienes tareas asignadas)\n");
}
