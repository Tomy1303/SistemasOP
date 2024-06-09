#include <stdio.h>
#include "builtin_setenv.h"

// Función para ejecutar el comando setenv
int execute_setenv(int argc, char **argv) {
    // Verificar si se pasaron exactamente 3 argumentos
    if (argc == 3) {
        // Intentar establecer la variable de entorno
        if (setenv(argv[1], argv[2], 1) == 0) {
            // Si se estableció correctamente, imprimir un mensaje de éxito
            printf("Variable de entorno %s establecida con valor %s\n", argv[1], argv[2]);
        } else {
            // Si hubo un error, imprimir un mensaje de error
            perror("Error al establecer la variable de entorno");
            return 1; // Retornar 1 para indicar que hubo un error
        }
        return 0; // Retornar 0 para indicar que la función se ejecutó correctamente
    } else {
        // Si no se pasaron 3 argumentos, imprimir un mensaje de uso
        fprintf(stderr, "Uso: %s <variable> <valor>\n", argv[0]);
        return 1; // Retornar 1 para indicar que hubo un error
    }
}