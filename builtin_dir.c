#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

// Función para ejecutar el comando 'dir'
int execute_dir(int argc, char **argv){
//Verifica si el número de argumentos es menor o igual a 2
    if(argc<=2){
//Obtiene el directorio actual de trabajo y lo almacena en 'este_dir'
        char *este_dir = getcwd(NULL,0);
// Almacena el segundo argumento en 'palabra' (la palabra a buscar)
        char *palabra = argv[1];
// Abre el directorio actual
        DIR *dir = opendir(este_dir);
// Declara una estructura para almacenar las entradas del directorio
        struct dirent *entry;
// Itera sobre cada entrada en el directorio
        while ((entry = readdir(dir)) != NULL) {
// Si se ha proporcionado una palabra para buscar
            if(palabra != NULL){
// Verifica si la palabra se encuentra en el nombre de la entrada
                if(strstr(entry->d_name, palabra) != NULL){
// Si se encuentra, imprime el nombre de la entrada
                     printf("%s\n", entry->d_name);
                }
// Si no se proporciona una palabra, imprime el nombre de todas las entradas
            }else{
                 printf("%s\n", entry->d_name);
            }
        }
    }
}