#include <stdio.h>
#include <stdlib.h>

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

void guardarComandos() {
    FILE *archivo = fopen("minish_history.txt", "w");
    if (archivo == NULL) {
        perror("fopen");
        exit(1);
    }
    nodo_historial *actual = head;
    while (actual != NULL) {
        fprintf(archivo, "%s\n", actual->comando);
        actual = actual->siguiente;
    }
    fclose(archivo);
}

void liberarLista() {
    nodo_historial *actual = head;
    while (actual != NULL) {
        nodo_historial *temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
}

void cargarComandos() {
    FILE *archivo = fopen("minish_history.txt", "r");
    if (archivo == NULL) {
        return; // No mostrar error si el archivo no existe
    }

    char linea[256];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        linea[strcspn(linea, "\n")] = '\0';
        agregar_historial(linea);
    }

    fclose(archivo);
}
