/*
 * auth.c - Autenticacion.
 */
#include <stdio.h>
#include <string.h>
#include "auth.h"
#include "usuarios.h"

/* Calcula el hash del username (dentro de buscarUsuario), llega a la cubeta y compara la contrasena. */
Usuario *iniciarSesion(const char *username, const char *password) {
    Usuario *u = buscarUsuario(username);
    if (!u) return NULL;
    if (strcmp(u->password, password) != 0) return NULL;
    return u;
}
