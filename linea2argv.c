#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int linea2argv(char *linea, int argc, char **argv) {
    int cantpalabras = 0;
    char *token = strtok(linea, " \t\n"); // Divide la línea en palabras

    while (token != NULL && cantpalabras < argc) {
        argv[cantpalabras] = strdup(token); // Asigna memoria para la palabra
        cantpalabras++;
        token = strtok(NULL, " \t\n"); // Siguiente palabra
    }

    return cantpalabras;
}



