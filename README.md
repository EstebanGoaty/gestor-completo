# Gestor Colaborativo de Proyectos (versión completa)

Aplicación de consola en C (Estructuras de Datos). Permite registrar usuarios, crear proyectos,
administrar integrantes y gestionar tareas con un tablero Kanban.

**TDAs usados**
- **Mapas / tablas hash** con cubetas encadenadas: usuarios (clave: username) y proyectos (clave: ID).
- **Listas enlazadas:** proyectos de cada usuario, integrantes de cada proyecto y tareas de cada proyecto.

## Compilar y ejecutar

```bash
make          # genera ./gestor
./gestor
make clean
```

Para detectar fugas de memoria: `valgrind --leak-check=full ./gestor`

## Estructura

```
tipos.h            structs y constantes
estado.h/.c        mapas globales y contadores de ID
utilidades.h/.c    leerLinea, leerEntero, textoEstado...
usuarios.h/.c      mapa hash de usuarios
auth.h/.c          inicio de sesión
menu_usuario.h/.c  menú inicial y menú del usuario
proyectos.h/.c     mapa hash de proyectos
integrantes.h/.c   relación usuario <-> proyecto (dos listas cruzadas)
tareas.h/.c        lista de tareas
vistas.h/.c        tablero Kanban y listados
menu_proyecto.h/.c menú del proyecto
memoria.h/.c       liberación de memoria
main.c             programa principal
```

## Decisiones de diseño
- Las contraseñas se guardan y comparan en texto plano.
- El creador de un proyecto no puede ser eliminado del mismo.
- Cada tarea tiene un ID propio dentro de su proyecto (T-01, T-02...).
- Los datos viven solo en memoria: se pierden al cerrar el programa.
