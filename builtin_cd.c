#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_PATH_LENGTH 1024

// Variable en donde se almacena el directorio anterior
char *previous_dir = NULL;

// Función para cambiar de directorio 
int execute_cd(int argc, char **argv) {
    char *dir;
    char current_dir[MAX_PATH_LENGTH];

    // Verificar si se ingresaron argumentos extra
    if (argc > 2) {
        fprintf(stderr, "Se proporcionaron muchos argumentos, intentelo otra vez\n");
        return 1;
    }

    // Si no se pasa ningún argumento, cambiar al directorio HOME del usuario
    if (argc == 1) {
        dir = getenv("HOME");
        if (!dir) {
            fprintf(stderr, "No esta establecido el HOME\n");
            return 1;
        }
    } else {
        // Si se le pasa un argumento, determinar el directorio de destino
        if (strcmp(argv[1], "-") == 0) {
            // Si el argumento es "-", cambiar al directorio ingresado anteriormente
            if (!previous_dir) {
                fprintf(stderr, "No se ha ingresado a un directorio anteriormente\n");
                return 1;
            }
            dir = previous_dir;
        } else {
            // Si el argumento no es "-", utilizar el argumento como directorio de destino
            dir = argv[1];
        }
    }

    // Obtener el directorio actual antes de cambiar
    if (!getcwd(current_dir, sizeof(current_dir))) {
        perror("No se pudo obtener el directorio actual");
        return 1;
    }

    // Cambiar al directorio especificado
    if (chdir(dir) != 0) {
        perror("No se pudo acceder al directorio especificado");
        return 1;
    }

    // Liberar la memoria ocupada por el directorio anterior y actualizarlo
    if (previous_dir) {
        free(previous_dir);
    }
    previous_dir = strdup(current_dir);

    // Obtener el directorio actual después del cambio
    if (!getcwd(current_dir, sizeof(current_dir))) {
        perror("No se pudo obtener el directorio actual");
        return 1;
    }

    // Actualizar la variable PWD con el directorio actual
    if (setenv("PWD", current_dir, 1) != 0) {
        perror("Error al actualizar PWD");
        return 1;
    }

    // Devolver 0 si termina correctamente
    return 0;
}
