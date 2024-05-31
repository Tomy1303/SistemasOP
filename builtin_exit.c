#include <stdio.h>
#include "builtin_exit.h"
#include "builtin_history.h"

int execute_exit(int argc, char **argv){
// Verifica si se ha pasado exactamente un argumento (es decir, solo el comando 'exit' sin parámetros adicionales).
    if(argc == 1){
        exit(0); // Termina el programa con un código de salida 0, indicando éxito.
    }else{
// Termina el programa con el código de salida especificado por el primer argumento después del comando 'exit'.
        exit(argv[1]);
    }
}