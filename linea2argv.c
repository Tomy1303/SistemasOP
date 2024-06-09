#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función que convierte una línea de texto en un array de palabras (argumentos)
int linea2argv(char *linea, int argc, char **argv) {
    int cantpalabras = 0;  // Inicializa el contador de palabras a 0
    // Utiliza strtok para dividir la línea en palabras separadas por espacios, tabulaciones o nuevas líneas
    char *token = strtok(linea, " \t\n");

    // Mientras haya palabras y no se haya alcanzado el número máximo de argumentos
    while (token != NULL && cantpalabras < argc) {
        // Duplica la palabra actual y la almacena en el array argv
        argv[cantpalabras] = strdup(token);
        cantpalabras++; // Incrementa el contador de palabras
        // Obtiene la siguiente palabra
        token = strtok(NULL, " \t\n");
    }

    return cantpalabras; // Devuelve la cantidad de palabras encontradas
}



