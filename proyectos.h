/* proyectos.h - Mapa hash de proyectos (clave: ID). Responsable: INTEGRANTE 3 */
#ifndef PROYECTOS_H
#define PROYECTOS_H

#include "tipos.h"

/* Convierte un ID en el numero de una cubeta (0 .. TAM_MAPA-1). */
unsigned hashEntero(int id);

/* Busca un proyecto por ID. Devuelve NULL si no existe. */
Proyecto *buscarProyecto(int id);

/* Crea un proyecto, lo inserta en el mapa y agrega al creador como primer integrante. */
Proyecto *crearProyecto(Usuario *creador, const char *nombre, const char *descripcion);

/* Muestra los proyectos en los que participa el usuario (recorre u->proyectos). */
void listarProyectos(const Usuario *u);

#endif
