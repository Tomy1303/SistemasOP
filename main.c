#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <signal.h>
#include <errno.h>
#include "minish.h"

#define MAX_INPUT_LENGTH 1024  //valores arbitrarios para ambos, buscamos nuemeros estandares que se adecuen con el proyecto
#define MAX_ARGC 100

void manejar_ctrl_c(int sig) {
    printf("\n(minish) %s:%s > ", getenv("USER"), getcwd(NULL, 0));
    fflush(stdout);
}