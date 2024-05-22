#include <stdio.h>
#include "fun_setenv.h"

int execute_setenv(int argc, char **argv){
    if(argc = 3){
        if (setenv(argv[1], argv[2], 1) == 0) {
        printf("Variable de entorno %s establecida con valor %s\n", argv[1], argv[2]);
    } else {
        perror("Error al establecer la variable de entorno");
    }

    return 0;
    }
}
