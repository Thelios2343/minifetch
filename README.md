 SysInfo

Pequeño programa en C que muestra información básica del sistema.

## Archivos

- `main.c` → punto de entrada del programa  
- `sysinfo.c` → lógica principal del sistema  
- `sysinfo.h` → declaraciones de funciones  
- `ansicolors.h` → macros para colores en terminal  
- `Makefile` → automatiza la compilación  

---

## Compilación

Para compilar el proyecto:

```bash
make

Esto genera el ejecutable:

./program
 Limpieza

Eliminar archivos objeto:

make clean

Eliminar todo (incluyendo el ejecutable):

make fclean

Recompilar desde cero:

make re
Ejecución

Después de compilar:

./program

Estructura del proyecto
.
├── Makefile
├── main.c
├── sysinfo.c
├── sysinfo.h
├── ansicolors.h
└── README.md

Notas
Compilado con gcc
Flags: -Wall -Wextra -Werror
Diseñado para Linux
