#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct builtin_struct {
    char *cmd; // nombre del comando interno
    int (*func) (int, char **); // la función que lo ejecuta
    char *help_txt; // el texto de ayuda
};

extern struct builtin_struct builtin_arr[];
extern struct builtin_struct *builtin_lookup(char *cmd);

int execute_exit(int argc, char **argv){
    exit(0);
}

struct builtin_struct builtin_arr[] = {
    {"exit", execute_exit, "Termina el shell. Admite un parámetro que es el estado de retorno. Sin parámetro, usa el estado de retorno del último comando ejecutado."},
    //{"pid", execute_pid, "Muestra el ID del proceso del shell."},
    //{"uid", execute_uid, "Muestra el ID de usuario como número y el nombre de usuario."},
    //{"gid", execute_gid, "Muestra el grupo principal y los grupos secundarios del usuario."},
    //{"getenv", execute_getenv, "Muestra el valor de la(s) variable(s) de entorno especificada(s). Los parámetros son las variables de entorno para las cuales se quiere saber el valor."},
    //{"setenv", execute_setenv, "Define una nueva variable de entorno o cambia el valor de una variable de entorno existente."},
    //{"unsetenv", execute_unsetenv, "Elimina variables de entorno."},
    //{"cd", execute_cd, "Cambia el directorio actual. Admite un parámetro. Además, setea la variable de entorno PWD con el pathname absoluto del directorio actual. El valor del parámetro puede ser: 'cd xxx' (cambia al directorio xxx), 'cd -' (cambia al directorio anterior), 'cd' (cambia al directorio especificado en la variable de entorno HOME)."},
    //{"status", execute_status, "Muestra el estado de retorno del último comando ejecutado."},
    //{"help", execute_help, "Muestra una ayuda más extensa para el comando especificado. Sin argumentos, muestra un texto de ayuda indicando qué comandos internos existen."},
    //{"dir", execute_dir, "Simula una ejecución simplificada del comando ls -l. Sin argumentos, muestra la lista de archivos del directorio actual. Con un único argumento, muestra la lista de archivos en el directorio especificado o que contengan el texto especificado en su nombre."},
    //{"history", execute_history, "Muestra los N comandos anteriores (por defecto 10) que deben almacenarse para ejecuciones posteriores del shell, en el archivo $HOME/.minish_history."},
    {NULL, NULL, NULL} // Marca de final de array
};

struct builtin_struct *builtin_lookup(char *cmd) {//buscar si existe el comando 
    struct builtin_struct *comando = builtin_arr;
    while (comando->cmd != NULL) {
        if (strcmp(comando->cmd, cmd) == 0) {//comparacion de comandos
            return comando;
        }
        comando++;
    }
    return NULL; // comando no encontrado
};

int ejecutar(int argc, char **argv) {
    struct builtin_struct *result = builtin_lookup(argv[0]);
    if (result != NULL) {
        result->func(argc, argv);
    }
    // Agrega un manejo para el caso en que el comando no se encuentra
    else {
        printf("Comando no encontrado: %s\n", argv[0]);
    }
    return 0; // Otra opción es devolver el estado de retorno de la función ejecutada
}






