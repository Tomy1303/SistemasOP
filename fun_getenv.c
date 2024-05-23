#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fun_getenv.h"

int execute_getenv(int argc, char **argv){
    for(int i =1 ; i < argc;i++){
        const char *var = argv[i];
        if (var != NULL) {
            printf("El valor de la variable %s es %s \n", var, getenv(var));
        }else{
            printf("La variable %s no está definida.\n", var);
            return 1;
        }
    }
    return 0;
}
