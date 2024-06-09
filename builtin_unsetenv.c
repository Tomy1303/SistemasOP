#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función para ejecutar el comando unsetenv
int execute_unsetenv(int argc, char **argv) {
    // Verificar si se pasaron exactamente 2 argumentos
    if (argc == 2) {
        // Intentar eliminar la variable de entorno
        if (unsetenv(argv[1]) == 0) {
            // Si se eliminó correctamente, imprimir un mensaje de éxito
            printf("Variable de entorno %s eliminada\n", argv[1]);
        } else {
            // Si hubo un error, imprimir un mensaje de error
            perror("Error al eliminar la variable de entorno");
            return 1; // Retornar 1 para indicar que hubo un error
        }
        return 0; // Retornar 0 para indicar que la función se ejecutó correctamente
    }
    // Si el número de argumentos es incorrecto, retornar 1
    fprintf(stderr, "Usage: unsetenv <variable>\n");
    return 1; // Retornar 1 para indicar que hubo un error
}