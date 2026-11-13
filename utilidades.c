/* utilidades.c - ARCHIVO COMPLETO. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilidades.h"

int leerLinea(const char *msg, char *buf, size_t n) {
    printf("%s", msg);
    fflush(stdout);
    if (!fgets(buf, (int)n, stdin)) return 0;
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        int c;                       /* descartar el resto de una linea demasiado larga */
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    return 1;
}

int leerEntero(const char *msg) {
    char buf[32];
    if (!leerLinea(msg, buf, sizeof buf)) return 0;
    char *fin;
    long v = strtol(buf, &fin, 10);
    if (fin == buf || *fin != '\0') return -1;
    return (int)v;
}

int vacio(const char *s) { return s[0] == '\0'; }

const char *textoEstado(Estado e) {
    switch (e) {
        case POR_HACER:   return "POR HACER";
        case EN_PROGRESO: return "EN PROGRESO";
        default:          return "TERMINADA";
    }
}

const char *textoPrioridad(int p) {
    switch (p) {
        case 1:  return "Baja";
        case 2:  return "Media";
        default: return "Alta";
    }
}

void noImplementado(const char *funcion) {
    printf("   [TODO] %s() aun no esta implementada.\n", funcion);
}
