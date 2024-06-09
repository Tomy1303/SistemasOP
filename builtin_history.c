#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wrappers.h"
#include "builtin_history.h"

// Definición de la estructura de un nodo del historial
typedef struct nodo_historial {
    char comando[256]; // Almacena el comando
    struct nodo_historial *siguiente; // Puntero al siguiente nodo
} nodo_historial;

// Variables globales
nodo_historial *head = NULL; // Puntero al inicio de la lista del historial
int counter = 0; // Contador de comandos en el historial
int size = 10; // Tamaño máximo del historial

// Función para agregar un comando al historial
void agregar_historial(const char *cmd) {
    // Crear un nuevo nodo y asignar memoria
    nodo_historial *nodo = (nodo_historial *)malloc(sizeof(nodo_historial));
    // Copiar el comando al nuevo nodo
    strncpy(nodo->comando, cmd, 256);
    if(counter==0){
        // guarda el primer comando
        counter++;
        head = nodo;
    }else{
        //Va hasta el final de la lista para agregar el nuevo comando
        nodo_historial *temp = head;
        for (int i = 1; i < counter; i++) {
            temp = temp->siguiente;
        }
        temp->siguiente = nodo;
        if (counter >= size) {
            // Borra el el nodo mas antiguo si hay mas de 10 elementos
            head=head->siguiente;
        }else{
            // Incrementar el contador si el historial no está lleno
            counter++;
        }
    }
}

// Función para imprimir el historial de comandos
void print_historial() {
    nodo_historial *temp = head; // Puntero temporal para recorrer la lista
    for (int i = 0; i < counter; i++) {
        // Imprimir el comando y avanzar al siguiente nodo
        printf("%d: %s\n", i, temp->comando);
        temp = temp->siguiente;
    }
}

// Función para ejecutar el comando de historial
int execute_history(int argc, char **argv) {
    // Imprimir el historial y retornar 0
    print_historial();
    return 0;
}

// Función para cargar el historial desde un archivo
void cargar_historial() {
    FILE *file = fopen_or_exit("minish_history.txt", "r"); // Abrir el archivo en modo lectura
    if (!file) return;

    char *line = NULL;
    size_t len = 0;

    // Leer cada línea del archivo
    while (getline(&line, &len, file) != -1) {
        // Eliminar el carácter de nueva línea
        line[strcspn(line, "\n")] = '\0'; 
        // Agregar el comando al historial
        agregar_historial(line);
    }
    fclose(file); // Cerrar el archivo
}

// Función para guardar un comando en el archivo de historial
void guardar_historial() {
    FILE *file = fopen_or_exit("minish_history.txt", "a"); // Abrir el archivo en modo adición
    if (!file) return;
    // Escribir el comando en el archivo
    nodo_historial *temp = head; // Puntero temporal para recorrer la lista
    for(int i = 0;i<counter;i++){
        fprintf(file, "%s\n", temp->comando);
        temp = temp->siguiente;
    }
    fclose(file); // Cerrar el archivo
}