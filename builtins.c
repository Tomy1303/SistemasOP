#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

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

int execute_help(int argc, char **argv){
    if(argc>1){
        struct builtin_struct *result = builtin_lookup(argv[1]);
        printf("%s",result->help_txt);
    }else{
        printf("comandos internos disponibles: \n 1-exit: Termina el shell. \n 2-help: Muestra ayuda para los comandos internos. \n 3-cd: Cambia el directorio actual.\n 4-dir: Simula una ejecución simplificada de ls -l. \n 5-history: Muestra comandos anteriores. \n 6-pid: Muestra el ID del proceso del shell. \n 7-uid: Muestra el ID de usuario como número y el nombre de usuario. \n 8-gid: Muestra el grupo principal y los grupos secundarios del usuario. \n 9-getenv: Muestra el valor de la(s) variable(s) de entorno especificada(s). Los parámetros son las variables de entorno para las cuales se quiere saber el valor. \n 10-setenv: Define una nueva variable de entorno o cambia el valor de una variable de entorno existente. \n 11-unsetenv: Elimina variables de entorno. \n 12-status: Muestra el estado de retorno del último comando ejecutado. \n");
    }
    return 0;
}

int execute_pid(int argc, char **argv){
    __pid_t pid = getpid();
    printf("El PID del proceso actual es: %d\n", pid);
    return 0;
}

int execute_uid(int argc, char **argv){
    __uid_t uid = getuid();
    printf("El UID del usuario actual es: %d\n", uid);
    struct passwd *user_entry = getpwuid(uid);
    if (user_entry != NULL) {
        printf("Nombre de usuario: %s\n", user_entry->pw_name);
    } else {
        printf("No se pudo obtener el nombre de usuario.\n");
    }
    return 0;
}

int execute_getenv(int argc, char **argv){
    for(int i =1 ; i < argc;i++){
        const char *var = argv[i];
        if (var != NULL) {
            printf("El valor de la variable %s es %s \n", var, getenv(var));
        }else{
            printf("La variable %s no está definida.\n", var);
        }
    }
    return 0;
}

int execute_setenv(int argc, char **argv){
    if(argc = 3){
        if (setenv(argv[1], argv[2], 1) == 0) {
        printf("Variable de entorno %s establecida con valor %s\n", argv[1], argv[2]);
    } else {
        perror("Error al establecer la variable de entorno");
    }

    return 0;
    }
}

struct builtin_struct builtin_arr[] = {
    {"exit", execute_exit, "Termina el shell. Admite un parámetro que es el estado de retorno. Sin parámetro, usa el estado de retorno del último comando ejecutado. \n"},
    {"pid", execute_pid, "Muestra el ID del proceso del shell. \n"},
    {"uid", execute_uid, "Muestra el ID de usuario como número y el nombre de usuario. \n"},
    //{"gid", execute_gid, "Muestra el grupo principal y los grupos secundarios del usuario. \n"},
    {"getenv", execute_getenv, "Muestra el valor de la(s) variable(s) de entorno especificada(s). Los parámetros son las variables de entorno para las cuales se quiere saber el valor. \n"},
    {"setenv", execute_setenv, "Define una nueva variable de entorno o cambia el valor de una variable de entorno existente. \n"},
    //{"unsetenv", execute_unsetenv, "Elimina variables de entorno. \n"},
    //{"cd", execute_cd, "Cambia el directorio actual. Admite un parámetro. Además, setea la variable de entorno PWD con el pathname absoluto del directorio actual. El valor del parámetro puede ser: 'cd xxx' (cambia al directorio xxx), 'cd -' (cambia al directorio anterior), 'cd' (cambia al directorio especificado en la variable de entorno HOME). \n"},
    //{"status", execute_status, "Muestra el estado de retorno del último comando ejecutado. \n"},
    {"help", execute_help, "Muestra una ayuda más extensa para el comando especificado. Sin argumentos, muestra un texto de ayuda indicando qué comandos internos existen. \n"},
    //{"dir", execute_dir, "Simula una ejecución simplificada del comando ls -l. Sin argumentos, muestra la lista de archivos del directorio actual. Con un único argumento, muestra la lista de archivos en el directorio especificado o que contengan el texto especificado en su nombre. \n"},
    //{"history", execute_history, "Muestra los N comandos anteriores (por defecto 10) que deben almacenarse para ejecuciones posteriores del shell, en el archivo $HOME/.minish_history. \n"},
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







