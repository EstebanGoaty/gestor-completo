/*
 * main.c - Punto de entrada. ARCHIVO COMPLETO.
 */
#include <stdio.h>
#include "menu_usuario.h"
#include "memoria.h"

int main(void) {
    printf("====================================\n");
    printf("   GESTOR COLABORATIVO DE PROYECTOS\n");
    printf("====================================\n");
    menuInicial();
    liberarTodo();
    printf("Hasta luego.\n");
    return 0;
}
