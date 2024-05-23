#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <signal.h>
#include <errno.h>
#include "linea2argv.h"
#include "builtins.h"

#define MAX_INPUT_LENGTH 1024 //valores arbitarios para ambos, buscamos valores estandres que se adecuen con el proyecto
#define MAX_ARGC 100
// Función que maneja la señal SIGINT (interrupción de Ctrl+C)
void manejar_interrupcion(int sig) {
    // Imprimir una nueva línea y el prompt del shell
    printf("\n(MiShell) %s:%s > ", getenv("USER"), getcwd(NULL, 0));
    // Limpiar la salida estándar
    fflush(stdout);
}
int ultimo_estado = 0;
int main() {
    char input[MAX_INPUT_LENGTH];
    char *argv[MAX_ARGC];
    int argc;

    // Configurar el manejador de señal para SIGINT
   // struct sigaction sa;
    //sa.sa_handler = manejar_interrupcion; // Establecer la función de manejo de señales
    //sigemptyset(&sa.sa_mask); // Limpiar el conjunto de señales bloqueadas
    //sa.sa_flags = SA_RESTART; // Establecer la bandera SA_RESTART para reiniciar llamadas interrumpidas
    //sigaction(SIGINT, &sa, NULL); // Registrar el manejador de señal

    // Bucle infinito para mantener el programa en ejecución continuamente
    while (1) {
        // Obtener el nombre de usuario y el directorio actual
        char *nombre_de_usuario = getenv("USER"); // Obtener el nombre de usuario actual
        char cwd[1024]; // Crear un buffer para almacenar el directorio actual

        // Verificar si se pudo obtener el directorio actual correctamente
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            // Si hubo un error al obtener el directorio actual, imprimir un mensaje de error y salir del programa
            perror("getcwd"); // Imprimir un mensaje de error describiendo el problema
            exit(EXIT_FAILURE); // Terminar el programa con un código de error
        }

        // Escribir el prompt string en stderr
        fprintf(stderr, "(minish) %s:%s > ", nombre_de_usuario, cwd);

        // Leer una línea de entrada
        if (fgets(input, sizeof(input), stdin) == NULL) {
            if (feof(stdin)) {
                break; // Salir del bucle si se encuentra EOF
            } else {
                perror("fgets");
                continue;
            }
        }

        // Separar la línea en palabras
        
        argc = linea2argv(input, MAX_ARGC, argv);

        if (argc < 0) {
            fprintf(stderr, "Error: Demasiados argumentos\n");
            continue;
        }

        // Invocar la función ejecutar

        ultimo_estado = ejecutar(argc, argv);

        // Limpiar la memoria asignada por linea2argv
        for (int i = 0; i < argc; i++) {
            free(argv[i]);
        }
    }

    return ultimo_estado;
}
