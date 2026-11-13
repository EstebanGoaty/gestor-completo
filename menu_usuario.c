/*
 * menu_usuario.c - Menu inicial y menu del usuario.
 */
#include <stdio.h>
#include "menu_usuario.h"
#include "menu_proyecto.h"
#include "auth.h"
#include "usuarios.h"
#include "proyectos.h"
#include "integrantes.h"
#include "vistas.h"
#include "utilidades.h"

void menuInicial(void) {
    int op;
    do {
        printf("\n--- MENU INICIAL ---\n1. Registrarse\n2. Iniciar sesion\n0. Salir\n");
        op = leerEntero("Seleccione una opcion: ");
        switch (op) {
        case 1: {
            char nom[LARGO_NOM], un[LARGO_NOM], pw[LARGO_NOM];
            leerLinea("Nombre completo: ", nom, sizeof nom);
            leerLinea("Username: ", un, sizeof un);
            leerLinea("Contrasena: ", pw, sizeof pw);
            if (vacio(nom) || vacio(un) || vacio(pw)) {
                printf("Todos los campos son obligatorios.\n");
                break;
            }
            if (registrarUsuario(nom, un, pw)) printf("Usuario registrado correctamente.\n");
            else printf("Ese username ya existe (o no hay memoria).\n");
            break;
        }
        case 2: {
            char un[LARGO_NOM], pw[LARGO_NOM];
            leerLinea("Username: ", un, sizeof un);
            leerLinea("Contrasena: ", pw, sizeof pw);
            Usuario *u = iniciarSesion(un, pw);
            if (!u) {
                printf("Credenciales incorrectas.\n");
            } else {
                printf("Bienvenido/a, %s.\n", u->nombre);
                menuUsuario(u);
            }
            break;
        }
        case 0:
            break;
        default:
            printf("Opcion invalida.\n");
        }
    } while (op != 0);
}

void menuUsuario(Usuario *u) {
    int op;
    do {
        printf("\n--- MENU DE %s ---\n1. Ver mis proyectos\n2. Crear proyecto\n"
               "3. Abrir proyecto (por ID)\n4. Revisar tareas asignadas\n0. Cerrar sesion\n",
               u->username);
        op = leerEntero("Seleccione una opcion: ");
        switch (op) {
        case 1:
            listarProyectos(u);
            break;
        case 2: {
            char nom[LARGO_NOM], desc[LARGO_DESC];
            leerLinea("Nombre del proyecto: ", nom, sizeof nom);
            if (vacio(nom)) { printf("El nombre no puede estar vacio.\n"); break; }
            leerLinea("Descripcion: ", desc, sizeof desc);
            Proyecto *p = crearProyecto(u, nom, desc);
            if (p) printf("Proyecto creado con ID %d.\n", p->id);
            else printf("Sin memoria disponible.\n");
            break;
        }
        case 3: {
            Proyecto *p = buscarProyecto(leerEntero("ID del proyecto: "));
            if (!p) printf("No existe ese proyecto.\n");
            else if (!esIntegrante(p, u)) printf("No eres integrante de ese proyecto.\n");
            else menuProyecto(u, p);
            break;
        }
        case 4:
            tareasAsignadas(u);
            break;
        case 0:
            break;
        default:
            printf("Opcion invalida.\n");
        }
    } while (op != 0);
}
