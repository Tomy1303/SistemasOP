#include <stdio.h>
#include "minish.h"

// Función para ejecutar el comando status
int execute_status(int argc, char **argv) {
    // Verificar si el número de argumentos es exactamente 1
    if (argc != 1) {
        // Si el número de argumentos es incorrecto, imprimir un mensaje de uso
        fprintf(stderr, "Usage: status\n");
        return 1; // Retornar 1 para indicar que hubo un error
    }
    // Imprimir el estado del último comando ejecutado que se obtiene del minish
    printf("Status del último comando ejecutado: %d\n", ultimo_estado);
    return ultimo_estado;; // Retornar 0 para indicar que la función se ejecutó correctamente
}
