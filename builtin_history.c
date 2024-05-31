#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wrappers.h"

typedef struct nodo_historial {
    char comando[256];
    struct nodo_historial *siguiente;
} nodo_historial;

nodo_historial *head = NULL;
int counter = 0;
int size = 10;

void agregar_historial(const char *cmd) {
    nodo_historial *nodo = (nodo_historial *)malloc(sizeof(nodo_historial));
    strncpy(nodo->comando, cmd, 256);
    nodo->siguiente = head;
    head = nodo;
    if (counter < size) {
        counter++;
    } else {
        nodo_historial *temp = head;
        for (int i = 1; i < size; i++) {
            temp = temp->siguiente;
        }
        free(temp->siguiente);
        temp->siguiente = NULL;
    }
}

void print_historial() {
    nodo_historial *temp = head;
    for (int i = 0; i < counter; i++) {
        printf("%d: %s\n", i, temp->comando);
        temp = temp->siguiente;
    }
}

int execute_history(int argc, char **argv) {
    print_historial();
    return 0;
}


void cargar_historial() {
    FILE *file = fopen_or_exit("minish_history.txt", "r");
    if (!file) return;

    char *line = NULL;

    size_t len=0;

    while (getline(&line, &len, file) != -1) {
        line[strcspn(line, "\n")] = '\0'; 
        agregar_historial(line);
    }
    fclose(file);
}

void guardar_historial(char *comand) {
    FILE *file = fopen_or_exit("minish_history.txt", "a");
    if (!file) return;
    fprintf(file, "%s\n", comand);
    fclose(file);
}

