#include <stdio.h>
#include "fun_exit.h"
#include "fun_history.h"

int execute_exit(int argc, char **argv){
    if(argc == 1){
        exit(0);
    }else{
        exit(argv[1]);
    }
}