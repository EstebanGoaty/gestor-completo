/* usuarios.h - Mapa hash de usuarios (clave: username). Responsable: INTEGRANTE 1 */
#ifndef USUARIOS_H
#define USUARIOS_H

#include "tipos.h"

/* Convierte un texto en el numero de una cubeta (0 .. TAM_MAPA-1). */
unsigned hashTexto(const char *s);

/* Busca un usuario por username. Devuelve NULL si no existe. */
Usuario *buscarUsuario(const char *username);

/* Busca un usuario por ID recorriendo todo el mapa. Devuelve NULL si no existe. */
Usuario *buscarUsuarioPorId(int id);

/* Crea e inserta un usuario nuevo. Devuelve NULL si el username ya existe o no hay memoria. */
Usuario *registrarUsuario(const char *nombre, const char *username, const char *password);

#endif
