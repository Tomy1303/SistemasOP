#include <stdio.h>
#include "minish.h"

int execute_status(int argc, char **argv){
    if (argc != 1) {
        fprintf(stderr, "Usage: status\n");
        return 1;
    }
    printf("Status del último comando ejecutado: %d\n", ultimo_estado);
    return 0;
}