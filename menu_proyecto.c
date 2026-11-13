/*
 * menu_proyecto.c - Menu de un proyecto abierto.
 */
#include <stdio.h>
#include "menu_proyecto.h"
#include "tareas.h"
#include "integrantes.h"
#include "vistas.h"
#include "utilidades.h"

/* Pide una prioridad valida (1..3). Si se cierra la entrada devuelve 1. */
static int pedirPrioridad(void) {
    int pr;
    do {
        pr = leerEntero("Prioridad (1 = Baja, 2 = Media, 3 = Alta): ");
        if (pr == 0) return 1;                                /* entrada cerrada */
        if (pr < 1 || pr > 3) printf("Prioridad invalida.\n");
    } while (pr < 1 || pr > 3);
    return pr;
}

void menuProyecto(Usuario *u, Proyecto *p) {
    int op;
    (void)u;
    do {
        printf("\n--- PROYECTO: %s ---\n"
               "1. Visualizar tablero de tareas\n2. Crear tarea\n3. Modificar tarea\n"
               "4. Eliminar tarea\n5. Asignar responsable\n6. Cambiar estado\n"
               "7. Administrar integrantes\n0. Volver\n", p->nombre);
        op = leerEntero("Seleccione una opcion: ");
        switch (op) {
        case 1:
            mostrarTablero(p);
            break;
        case 2: {
            char nom[LARGO_NOM], desc[LARGO_DESC];
            leerLinea("Nombre de la tarea: ", nom, sizeof nom);
            if (vacio(nom)) { printf("El nombre no puede estar vacio.\n"); break; }
            leerLinea("Descripcion: ", desc, sizeof desc);
            int pr = pedirPrioridad();
            Tarea *t = crearTarea(p, nom, desc, pr);
            if (t) printf("Tarea T-%02d creada (estado POR HACER).\n", t->id);
            else printf("Sin memoria disponible.\n");
            break;
        }
        case 3: {
            Tarea *t = buscarTarea(p, leerEntero("ID de la tarea: "));
            if (!t) { printf("No existe esa tarea.\n"); break; }
            char nom[LARGO_NOM], desc[LARGO_DESC];
            leerLinea("Nuevo nombre (Enter para mantener): ", nom, sizeof nom);
            if (!vacio(nom)) snprintf(t->nombre, sizeof t->nombre, "%s", nom);
            leerLinea("Nueva descripcion (Enter para mantener): ", desc, sizeof desc);
            if (!vacio(desc)) snprintf(t->descripcion, sizeof t->descripcion, "%s", desc);
            int pr = leerEntero("Nueva prioridad 1-3 (0 para mantener): ");
            if (pr >= 1 && pr <= 3) t->prioridad = pr;
            printf("Tarea actualizada.\n");
            break;
        }
        case 4:
            if (eliminarTarea(p, leerEntero("ID de la tarea a eliminar: "))) printf("Tarea eliminada.\n");
            else printf("No existe esa tarea.\n");
            break;
        case 5: {
            Tarea *t = buscarTarea(p, leerEntero("ID de la tarea: "));
            if (!t) { printf("No existe esa tarea.\n"); break; }
            char un[LARGO_NOM];
            leerLinea("Username del responsable: ", un, sizeof un);
            int r = asignarTarea(p, t, un);
            if (r == 0) printf("Tarea asignada a %s.\n", un);
            else if (r == 1) printf("No existe ese usuario.\n");
            else printf("Ese usuario no pertenece al proyecto.\n");
            break;
        }
        case 6: {
            Tarea *t = buscarTarea(p, leerEntero("ID de la tarea: "));
            if (!t) { printf("No existe esa tarea.\n"); break; }
            int e = leerEntero("Nuevo estado (1 = Por hacer, 2 = En progreso, 3 = Terminada): ");
            if (cambiarEstado(t, e) == 0) printf("Estado actualizado a %s.\n", textoEstado(t->estado));
            else printf("Estado invalido.\n");
            break;
        }
        case 7:
            menuIntegrantes(p);
            break;
        case 0:
            break;
        default:
            printf("Opcion invalida.\n");
        }
    } while (op != 0);
}
