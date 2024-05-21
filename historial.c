#include <stdio.h>
#include <stdlib.h>

typedef struct nodo_historial{
    char comando[256];
    struct nodo_historial *siguiente;
} nodo_historial;

nodo_historial *head = NULL;
int counter = 0;
int size = 10;

void agregar_historial(const char *cmd){
    nodo_historial *nodo = (nodo_historial *)malloc(sizeof(nodo_historial));
    strncpy(nodo->comando,cmd,256);
    nodo->siguiente = head;
    head = nodo;
    if(counter < size){
        counter++;
    }else{
        nodo_historial *temp = head;
        for(int i=1 ; i < size-1 ; i++){
            temp = temp->siguiente;
        }
        free(temp->siguiente);
        temp->siguiente = NULL;
    }
}

void print_historial(){
    nodo_historial *temp= head;
    for(int i=1;i<counter-1;i++){
        printf("\n", temp->comando);
        temp=temp->siguiente;
    }
}

