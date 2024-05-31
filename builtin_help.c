#include "builtins.h"
#include <stdio.h>  
#include "builtin_help.h"

int execute_help(int argc, char **argv){
    if(argc>1){
        struct builtin_struct *result = builtin_lookup(argv[1]);
        printf("%s",result->help_txt);
    }else{
        printf("comandos internos disponibles: \n 1-exit: Termina el shell. \n 2-help: Muestra ayuda para los comandos internos. \n 3-cd: Cambia el directorio actual.\n 4-dir: Simula una ejecución simplificada de ls -l. \n 5-history: Muestra comandos anteriores. \n 6-pid: Muestra el ID del proceso del shell. \n 7-uid: Muestra el ID de usuario como número y el nombre de usuario. \n 8-gid: Muestra el grupo principal y los grupos secundarios del usuario. \n 9-getenv: Muestra el valor de la(s) variable(s) de entorno especificada(s). Los parámetros son las variables de entorno para las cuales se quiere saber el valor. \n 10-setenv: Define una nueva variable de entorno o cambia el valor de una variable de entorno existente. \n 11-unsetenv: Elimina variables de entorno. \n 12-status: Muestra el estado de retorno del último comando ejecutado. \n");
    }
    return 0;
}