/*
 * integrantes.c - Relacion usuario <-> proyecto.
 * La relacion se guarda en DOS listas que siempre se actualizan juntas:
 *   p->integrantes (usuarios del proyecto)  y  u->proyectos (proyectos del usuario).
 */
#include <stdio.h>
#include <stdlib.h>
#include "integrantes.h"
#include "usuarios.h"
#include "estado.h"
#include "utilidades.h"

int esIntegrante(const Proyecto *p, const Usuario *u) {
    for (NodoIntegrante *n = p->integrantes; n; n = n->sig)
        if (n->usuario == u) return 1;
    return 0;
}

int agregarIntegrante(Proyecto *p, Usuario *u) {
    if (esIntegrante(p, u)) return 1;
    NodoIntegrante *ni = malloc(sizeof *ni);
    NodoProyecto   *np = malloc(sizeof *np);
    if (!ni || !np) { free(ni); free(np); return -1; }
    ni->usuario = u;  ni->sig = p->integrantes;  p->integrantes = ni;      /* nodo en el proyecto */
    np->proyecto = p; np->sig = u->proyectos;    u->proyectos = np;        /* nodo en el usuario  */
    return 0;
}

int eliminarIntegrante(Proyecto *p, Usuario *u) {
    if (!esIntegrante(p, u)) return 1;
    if (p->creador == u) return 2;

    NodoIntegrante *ant = NULL, *ni = p->integrantes;         /* desenlazar de la lista del proyecto */
    while (ni && ni->usuario != u) { ant = ni; ni = ni->sig; }
    if (ant) ant->sig = ni->sig; else p->integrantes = ni->sig;
    free(ni);

    NodoProyecto *antP = NULL, *np = u->proyectos;            /* desenlazar de la lista del usuario */
    while (np && np->proyecto != p) { antP = np; np = np->sig; }
    if (np) {
        if (antP) antP->sig = np->sig; else u->proyectos = np->sig;
        free(np);
    }

    for (Tarea *t = p->tareas; t; t = t->sig)                 /* sus tareas quedan sin asignar */
        if (t->idResponsable == u->id) t->idResponsable = 0;
    return 0;
}

void listarIntegrantes(const Proyecto *p) {
    printf("\n=== INTEGRANTES DE %s ===\n", p->nombre);
    for (NodoIntegrante *n = p->integrantes; n; n = n->sig)
        printf("   %-16s (%s)%s\n", n->usuario->username, n->usuario->nombre,
               n->usuario == p->creador ? "  <- creador" : "");
}

void menuIntegrantes(Proyecto *p) {
    int op;
    do {
        printf("\n--- INTEGRANTES (%s) ---\n1. Ver integrantes\n2. Agregar integrante\n"
               "3. Eliminar integrante\n0. Volver\n", p->nombre);
        op = leerEntero("Seleccione una opcion: ");
        if (op == 1) {
            listarIntegrantes(p);
        } else if (op == 2) {
            char un[LARGO_NOM];
            leerLinea("Username del usuario a agregar: ", un, sizeof un);
            Usuario *u = buscarUsuario(un);
            if (!u) { printf("No existe ese usuario.\n"); continue; }
            int r = agregarIntegrante(p, u);
            if (r == 0) printf("%s fue agregado al proyecto.\n", u->username);
            else if (r == 1) printf("Ese usuario ya es integrante.\n");
            else printf("Sin memoria disponible.\n");
        } else if (op == 3) {
            char un[LARGO_NOM];
            leerLinea("Username del integrante a eliminar: ", un, sizeof un);
            Usuario *u = buscarUsuario(un);
            if (!u) { printf("No existe ese usuario.\n"); continue; }
            int r = eliminarIntegrante(p, u);
            if (r == 0) printf("%s fue eliminado del proyecto (sus tareas quedaron sin asignar).\n", u->username);
            else if (r == 1) printf("Ese usuario no es integrante del proyecto.\n");
            else printf("No se puede eliminar al creador del proyecto.\n");
        } else if (op != 0) {
            printf("Opcion invalida.\n");
        }
    } while (op != 0);
}
