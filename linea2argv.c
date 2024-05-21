#include <stdio.h>

 int linea2argv (char *linea, int argc, char **argv){
    int cantpalabras;
    for (int i = 0; linea[i] != '\0'; i++) {
        if (linea[i] == ' ' || linea[i] == '\t' || linea[i] == '\n') {
            argv[i] = 0
        }
        if (count >= argc - 1) {
                    break;
                }
        else{
            argv[i] = linea[i]
            cantpalabras = i
        }
    return cantpalabras;
}

