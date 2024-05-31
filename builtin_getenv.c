#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "builtin_getenv.h"

// Función para ejecutar el comando getenv
int execute_getenv(int argc, char **argv){
 // Iteramos sobre los argumentos pasados a la función, comenzando desde el segundo argumento
    for(int i =1 ; i < argc;i++){
        const char *var = argv[i]; // Obtenemos el nombre de la variable del argumento actual
        if (var != NULL) { // Comprobamos si el nombre de la variable no es nulo
 // Imprimimos el nombre de la variable y su valor utilizando la función getenv
            printf("El valor de la variable %s es %s \n", var, getenv(var));
        }else{
// Si el nombre de la variable es nulo, imprimimos un mensaje indicando que no está definida
            printf("La variable %s no está definida.\n", var);
            return 1; // Salimos de la función con un código de error
        }
    }
    return 0;// Si todo salió bien, retornamos 0 para indicar éxito
}
