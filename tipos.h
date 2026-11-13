/*
 * tipos.h - Estructuras de datos y constantes compartidas.
 * ARCHIVO COMPLETO: no hace falta modificarlo (si cambias algo, avisa al grupo).
 */
#ifndef TIPOS_H
#define TIPOS_H

#define TAM_MAPA   31      /* numero de cubetas de cada mapa hash */
#define LARGO_NOM  50
#define LARGO_DESC 120

typedef enum { POR_HACER = 1, EN_PROGRESO, TERMINADA } Estado;

struct Usuario;
struct Proyecto;

/* ---- Tarea: nodo de la lista de tareas de un proyecto ---- */
typedef struct Tarea {
    int id;                          /* unico dentro del proyecto */
    char nombre[LARGO_NOM];
    char descripcion[LARGO_DESC];
    int prioridad;                   /* 1 = Baja, 2 = Media, 3 = Alta */
    Estado estado;
    int idResponsable;               /* ID de usuario; 0 = sin asignar */
    struct Tarea *sig;
} Tarea;

/* ---- Nodo de referencia: un proyecto dentro de la lista de un usuario ---- */
typedef struct NodoProyecto {
    struct Proyecto *proyecto;
    struct NodoProyecto *sig;
} NodoProyecto;

/* ---- Nodo de referencia: un usuario dentro de la lista de un proyecto ---- */
typedef struct NodoIntegrante {
    struct Usuario *usuario;
    struct NodoIntegrante *sig;
} NodoIntegrante;

/* ---- Usuario: elemento del mapa de usuarios (clave: username) ---- */
typedef struct Usuario {
    int id;
    char nombre[LARGO_NOM];
    char username[LARGO_NOM];
    char password[LARGO_NOM];
    NodoProyecto *proyectos;         /* lista de proyectos asociados */
    struct Usuario *sigCubeta;       /* encadenamiento dentro de la cubeta */
} Usuario;

/* ---- Proyecto: elemento del mapa de proyectos (clave: ID) ---- */
typedef struct Proyecto {
    int id;
    char nombre[LARGO_NOM];
    char descripcion[LARGO_DESC];
    Usuario *creador;
    NodoIntegrante *integrantes;     /* lista de integrantes */
    Tarea *tareas;                   /* lista de tareas */
    int siguienteIdTarea;            /* contador de IDs de tarea */
    struct Proyecto *sigCubeta;      /* encadenamiento dentro de la cubeta */
} Proyecto;

#endif
