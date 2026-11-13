/*
 * usuarios.c - Mapa hash de usuarios (clave: username).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "estado.h"

/* Funcion hash djb2: convierte un texto en el indice de una cubeta. */
unsigned hashTexto(const char *s) {
    unsigned h = 5381;
    while (*s) h = h * 33u + (unsigned char)*s++;
    return h % TAM_MAPA;
}

/* hash -> cubeta -> recorrer la cadena comparando usernames. */
Usuario *buscarUsuario(const char *username) {
    Usuario *u = mapaUsuarios[hashTexto(username)];
    while (u && strcmp(u->username, username) != 0) u = u->sigCubeta;
    return u;
}

/* La clave del mapa es el username, asi que buscar por ID recorre todo (O(U)). */
Usuario *buscarUsuarioPorId(int id) {
    for (int i = 0; i < TAM_MAPA; i++)
        for (Usuario *u = mapaUsuarios[i]; u; u = u->sigCubeta)
            if (u->id == id) return u;
    return NULL;
}

Usuario *registrarUsuario(const char *nombre, const char *username, const char *password) {
    if (buscarUsuario(username)) return NULL;                 /* username duplicado */
    Usuario *u = malloc(sizeof *u);
    if (!u) return NULL;
    u->id = siguienteIdUsuario++;
    snprintf(u->nombre, sizeof u->nombre, "%s", nombre);
    snprintf(u->username, sizeof u->username, "%s", username);
    snprintf(u->password, sizeof u->password, "%s", password);
    u->proyectos = NULL;
    unsigned c = hashTexto(username);                         /* insercion al inicio de la cubeta */
    u->sigCubeta = mapaUsuarios[c];
    mapaUsuarios[c] = u;
    return u;
}
