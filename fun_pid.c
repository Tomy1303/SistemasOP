#include "fun_pid.h"
#include <pwd.h>
#include <stdio.h>

int execute_pid(int argc, char **argv){
    __pid_t pid = getpid();
    printf("El PID del proceso actual es: %d\n", pid);
    return 0;
}