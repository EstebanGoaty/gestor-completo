/*
 * memoria.c - Liberar toda la memoria dinamica al cerrar el programa.
 */
#include <stdlib.h>
#include "memoria.h"
#include "estado.h"

void liberarTodo(void) {
    for (int i = 0; i < TAM_MAPA; i++) {
        Proyecto *p = mapaProyectos[i];
        while (p) {
            Proyecto *sigP = p->sigCubeta;                    /* guardar el siguiente ANTES de liberar */
            for (Tarea *t = p->tareas; t; ) { Tarea *s = t->sig; free(t); t = s; }
            for (NodoIntegrante *n = p->integrantes; n; ) { NodoIntegrante *s = n->sig; free(n); n = s; }
            free(p);
            p = sigP;
        }
        mapaProyectos[i] = NULL;
    }
    for (int i = 0; i < TAM_MAPA; i++) {
        Usuario *u = mapaUsuarios[i];
        while (u) {
            Usuario *sigU = u->sigCubeta;
            for (NodoProyecto *n = u->proyectos; n; ) { NodoProyecto *s = n->sig; free(n); n = s; }
            free(u);
            u = sigU;
        }
        mapaUsuarios[i] = NULL;
    }
}
