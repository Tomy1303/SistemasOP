#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int execute_unsetenv(int argc, char **argv){
    if(argc == 2){
        if (unsetenv(argv[1]) == 0) {
            printf("Variable de entorno %s eliminada\n", argv[1]);
        } else {
            perror("Error al eliminar la variable de entorno");
            return 1;
        }

        return 0;
    }
    return 1;
}