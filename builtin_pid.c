#include "builtin_pid.h"
#include <pwd.h>
#include <stdio.h>

// Función para ejecutar el comando pid
int execute_pid(int argc, char **argv) {
    __pid_t pid = getpid(); // Obtener el PID del proceso actual
    printf("El PID del proceso actual es: %d\n", pid); // Imprimir el PID del proceso actual
    return 0; // Retornar 0 para indicar que la función se ejecutó correctamente
}