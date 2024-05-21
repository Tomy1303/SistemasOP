#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <signal.h>
#include <errno.h>
#include "minish.h"

#define MAX_INPUT_LENGTH 1024 //valores arbitarios para ambos, buscamos valores estandres que se adecuen con el proyecto
#define MAX_ARGC 100
// Función que maneja la señal SIGINT (interrupción de Ctrl+C)
void manejar_interrupcion(int sig) {
    // Imprimir una nueva línea y el prompt del shell
    printf("\n(MiShell) %s:%s > ", getenv("USER"), getcwd(NULL, 0));
    // Limpiar la salida estándar
    fflush(stdout);
}
int main() {
    // Configurar el manejador de señal para SIGINT
    struct sigaction sa;
    sa.sa_handler = manejar_interrupcion; // Establecer la función de manejo de señales
    sigemptyset(&sa.sa_mask); // Limpiar el conjunto de señales bloqueadas
    sa.sa_flags = SA_RESTART; // Establecer la bandera SA_RESTART para reiniciar llamadas interrumpidas
    sigaction(SIGINT, &sa, NULL); // Registrar el manejador de señal

    // Resto del código del shell...
    
    return 0;
}
   // Bucle infinito para mantener el programa en ejecución continuamente
while (1) {
    // Obtener el nombre de usuario y el directorio actual
    char *username = getenv("USER"); // Obtener el nombre de usuario actual
    char cwd[1024]; // Crear un buffer para almacenar el directorio actual

    // Verificar si se pudo obtener el directorio actual correctamente
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        // Si hubo un error al obtener el directorio actual, imprimir un mensaje de error y salir del programa
        perror("getcwd"); // Imprimir un mensaje de error describiendo el problema
        exit(EXIT_FAILURE); // Terminar el programa con un código de error
    }

    // En este punto, `username` contiene el nombre de usuario actual y `cwd` contiene el directorio actual

    // Resto del código para procesar el directorio actual y el nombre de usuario...
}
