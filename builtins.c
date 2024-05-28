#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <errno.h>
#include <error.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "builtins.h"
#include "fun_help.h"
#include "fun_exit.h"
#include "fun_pid.h"
#include "fun_uid.h"
#include "fun_getenv.h"
#include "fun_setenv.h"
#include "fun_unsetenv.h"
#include "fun_gid.h"
#include "fun_status.h"
#include "fun_cd.h"
#include "fun_dir.h"
#include "fun_history.h"

extern struct builtin_struct builtin_arr[];
extern struct builtin_struct *builtin_lookup(char *cmd);

struct builtin_struct builtin_arr[] = {
    {"exit", execute_exit, "Termina el shell. Admite un parámetro que es el estado de retorno. Sin parámetro, usa el estado de retorno del último comando ejecutado. \n"},
    {"pid", execute_pid, "Muestra el ID del proceso del shell. \n"},
    {"uid", execute_uid, "Muestra el ID de usuario como número y el nombre de usuario. \n"},
    {"gid", execute_gid, "Muestra el grupo principal y los grupos secundarios del usuario. \n"},
    {"getenv", execute_getenv, "Muestra el valor de la(s) variable(s) de entorno especificada(s). Los parámetros son las variables de entorno para las cuales se quiere saber el valor. \n"},
    {"setenv", execute_setenv, "Define una nueva variable de entorno o cambia el valor de una variable de entorno existente. \n"},
    {"unsetenv", execute_unsetenv, "Elimina variables de entorno. \n"},
    {"cd", execute_cd, "Cambia el directorio actual. Admite un parámetro. Además, setea la variable de entorno PWD con el pathname absoluto del directorio actual. El valor del parámetro puede ser: 'cd xxx' (cambia al directorio xxx), 'cd -' (cambia al directorio anterior), 'cd' (cambia al directorio especificado en la variable de entorno HOME). \n"},
    {"status", execute_status, "Muestra el estado de retorno del último comando ejecutado. \n"},
    {"help", execute_help, "Muestra una ayuda más extensa para el comando especificado. Sin argumentos, muestra un texto de ayuda indicando qué comandos internos existen. \n"},
    {"dir", execute_dir, "Simula una ejecución simplificada del comando ls -l. Sin argumentos, muestra la lista de archivos del directorio actual. Con un único argumento, muestra la lista de archivos en el directorio especificado o que contengan el texto especificado en su nombre. \n"},
    {"history", execute_history, "Muestra los N comandos anteriores (por defecto 10) que deben almacenarse para ejecuciones posteriores del shell, en el archivo $HOME/.minish_history. \n"},
    {"cd", execute_cd, "Cambia el directorio actual. Admite un parámetro. Además, setea la variable de entorno PWD con el pathname absoluto del directorio actual. El valor del parámetro puede ser: 'cd xxx' (cambia al directorio xxx), 'cd -' (cambia al directorio anterior), 'cd' (cambia al directorio especificado en la variable de entorno HOME). \n"},
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
    int status = 0;

    if (argc == 1) {
        agregar_historial(argv[0]);
        
    } else {
        size_t length = strlen(argv[0]) + strlen(argv[1]) + 2;
        char *palabras = (char *)malloc(length * sizeof(char));
        strcpy(palabras, argv[0]);
        strcat(palabras, " ");
        strcat(palabras, argv[1]);
        agregar_historial(palabras);
        free(palabras);
    }

    if (result != NULL) {
        status = result->func(argc, argv);
    } else {
        status = externo(argc, argv);
    }

    return status;
}
void sigint_handler(int signum) {                    // the handler for SIGINT
    fprintf(stderr, "Interrupt! (signal number %d)\n", signum);
}

int externo (int argc, char **argv){

    struct sigaction oldact, newact;

    sigaction(SIGINT, NULL, &newact);           // the  previous action for SIGINT is saved in oldact
    newact.sa_handler = sigint_handler;
    sigaction(SIGINT, &newact, NULL);           // set SIGINT handler for loop

    pid_t pid = fork();

    sigaction(SIGINT, NULL, &oldact);   // the  previous action for SIGINT is saved in oldact
    newact = oldact;

    if (pid == -1) {
        perror("fork");
        return 1;
    }
    if(pid == 0){
        newact.sa_handler = SIG_IGN;
        sigaction(SIGINT, &newact, NULL);   // reset SIGINT default for child
        execvp(argv[0],argv);
        printf("El comando terminó anormalmente.\n");
        fflush(stdout);
        exit(1);
    }else{
        newact.sa_handler = SIG_IGN;
        sigaction(SIGINT, &newact, NULL);   // ignore SIGINT while waiting
        wait(NULL);

        sigaction(SIGINT, &oldact, NULL);   // restore SIGINT when child finishes
    }
    return 0;
}
