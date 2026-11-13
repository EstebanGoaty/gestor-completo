/*
 * proyectos.c - Mapa hash de proyectos (clave: ID).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proyectos.h"
#include "integrantes.h"
#include "estado.h"

unsigned hashEntero(int id) {
    return (unsigned)id % TAM_MAPA;
}

Proyecto *buscarProyecto(int id) {
    Proyecto *p = mapaProyectos[hashEntero(id)];
    while (p && p->id != id) p = p->sigCubeta;
    return p;
}

Proyecto *crearProyecto(Usuario *creador, const char *nombre, const char *descripcion) {
    Proyecto *p = malloc(sizeof *p);
    if (!p) return NULL;
    p->id = siguienteIdProyecto++;
    snprintf(p->nombre, sizeof p->nombre, "%s", nombre);
    snprintf(p->descripcion, sizeof p->descripcion, "%s", descripcion);
    p->creador = creador;
    p->integrantes = NULL;
    p->tareas = NULL;
    p->siguienteIdTarea = 1;
    unsigned c = hashEntero(p->id);                           /* insercion al inicio de la cubeta */
    p->sigCubeta = mapaProyectos[c];
    mapaProyectos[c] = p;
    agregarIntegrante(p, creador);                            /* el creador es el primer integrante */
    return p;
}

void listarProyectos(const Usuario *u) {
    printf("\n=== PROYECTOS DE %s ===\n", u->username);
    if (!u->proyectos) {
        printf("   (no participas en ningun proyecto)\n");
        return;
    }
    for (NodoProyecto *n = u->proyectos; n; n = n->sig)
        printf("   [ID %d] %-24s %s\n", n->proyecto->id, n->proyecto->nombre, n->proyecto->descripcion);
}
