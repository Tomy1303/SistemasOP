#include "builtins.h"
#include <stdio.h>  
#include "builtin_help.h"

// Función para ejecutar el comando 'help'
int execute_help(int argc, char **argv) {
    // Si hay más de un argumento, se asume que es un comando específico para mostrar su ayuda
    if (argc > 1) {
        struct builtin_struct *result = builtin_lookup(argv[1]); // Busca el comando en los comandos internos
        if (result != NULL) { // Si se encuentra el comando, muestra su texto de ayuda
            printf("%s", result->help_txt);
        } else { // Si el comando no se encuentra, muestra un mensaje de error
            printf("Ese comando no existe \n");
            return 1;
        }
    } else { // Si no se proporciona un comando específico, muestra la lista de comandos internos disponibles
        printf("Comandos internos disponibles: \n");
        printf("1 - exit: Termina el shell. \n");
        printf("2 - help: Muestra ayuda para los comandos internos. \n");
        printf("3 - cd: Cambia el directorio actual.\n");
        printf("4 - dir: Simula una ejecución simplificada de ls -l. \n");
        printf("5 - history: Muestra comandos anteriores. \n");
        printf("6 - pid: Muestra el ID del proceso del shell. \n");
        printf("7 - uid: Muestra el ID de usuario como número y el nombre de usuario. \n");
        printf("8 - gid: Muestra el grupo principal y los grupos secundarios del usuario. \n");
        printf("9 - getenv: Muestra el valor de la(s) variable(s) de entorno especificada(s). \n");
        printf("10 - setenv: Define una nueva variable de entorno o cambia el valor de una variable de entorno existente. \n");
        printf("11 - unsetenv: Elimina variables de entorno. \n");
        printf("12 - status: Muestra el estado de retorno del último comando ejecutado. \n");
    }
    return 0; // Retorna 0 para indicar que el comando se ejecutó correctamente
}