#define MAXLINE 1024        // tamaño máximo de la línea de entrada
#define MAXCWD 1024         // tamaño máximo para alojar el pathname completo del directorio corriente
#define MAXWORDS 256        // cantidad máxima de palabras en la línea
#define MAXALIAS 256        // cantidad máxima de alias
#define HISTORY_FILE	".minish_history"   // nombre del archivo que almacena historia de comandos

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <error.h>
#include <errno.h>
/*
#include <signal.h>
#include <pwd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

*/
// Variables que deberán definirse en el main o en otro archivo fuente
extern int globalstatret;   // guarda status del ultimo comando - deberá definirse en el main
extern char cwd[MAXCWD];    // almacena el current working directory
extern int ultimo_estado;

// Funciones
extern int builtin_alias (int argc, char ** argv);
extern int builtin_copiar (int argc, char ** argv);
extern int builtin_basedirname (int argc, char **argv);
extern int builtin_exit (int argc, char ** argv);
extern int builtin_help (int argc, char ** argv);
extern int builtin_history (int argc, char ** argv);
extern int builtin_mes (int argc, char ** argv);
extern int builtin_status (int argc, char ** argv);
extern int builtin_cd (int argc, char ** argv);
extern int builtin_dir (int argc, char ** argv);
extern int builtin_getenv (int argc, char ** argv);
extern int builtin_gid (int argc, char ** argv);
extern int builtin_setenv (int argc, char ** argv);
extern int builtin_pid (int argc, char ** argv);
extern int builtin_uid (int argc, char ** argv);
extern int builtin_unsetenv (int argc, char ** argv);
extern int ejecutar (int argc, char ** argv);
extern int externo (int argc, char ** argv);
extern int linea2argv(char *linea, int argc, char **argv);

struct builtin_struct {         // struct con información de los builtins
    char *cmd;                  // nombre del comando builtin
    int (*func) (int, char **); // la función que lo ejecuta
    char *help_txt;             // el texto de ayuda
};

struct hist_st {                // struct para armar la history de comandos
    char **linearray;           // array de líneas de comando
    size_t arraysize;           // tamaño del array anterior
    size_t used;                // usados del array anterior
};

struct alias_struct {           // struct para guardar los alias
    char *cmd;                  // nombre del alias
    char **argv;                // lista de palabras asociadas al alias
    int argc;                   // largo de la lista anterior
};


struct alias_treenode {         // nodo de un árbol binario simple
    struct alias_struct *alias; // alias apuntado por este nodo
    struct alias_treenode *left, *right; // punteros a subárbol izquierdo y derecho
};

extern struct alias_treenode *alias_treenode_root;
extern struct alias_struct *alias_lookup(struct alias_treenode *root, char *cmd);
extern struct builtin_struct builtin_arr[];
extern struct builtin_struct *builtin_lookup(char *cmd);
extern struct hist_st *history_file_lines, *history_session_lines;
extern struct hist_st *history_init(FILE *fp);
extern struct hist_st *history_addline(struct hist_st *ph, char *line);
extern void history_append_session_lines(int status, FILE *fphist);

/*
    builtin_arr es una lista de los builtins, que se recorrerá en forma lineal.
    Podría usarse una estructura que mejorara la velocidad de búsqueda, pero
    en este ejercicio una lista que se recorre en forma lineal es suficiente.
    Deberá definirse e inicializarse como variable global, de esta manera:
    struct builtin_struct builtin_arr[] = {
        { "cd", builtin_cd, HELP_CD },
        .... etc. etc.
        { "uid", builtin_uid, HELP_UID },
        { NULL, NULL, NULL }
    };
    La definición no puede hacerse en este archivo minish.h porque está pensado
    para ser incluido en todos los fuentes y no se puede definir el mismo array en
    diferentes fuentes de un mismo programa.
*/

/*
    La siguiente lista de constantes de texto puede adaptarse/mejorarse, se pone como ejemplo.
    Lo lógico sería que estuvieran definidas en el mismo fuente que define el array builtin_arr
    en lugar de estar en este archivo .h.

#define HELP_CD      "cd [..|dir] - cambia de directorio corriente"
#define HELP_DIR     "dir [str]- muestra archivos en directorio corriente, que tengan 'str'"
#define HELP_EXIT    "exit [status] - finaliza el minish con un status de retorno (por defecto 0)"
#define HELP_HELP    "help [cd|dir|exit|help|history|getenv|pid|setenv|status|uid]"
#define HELP_HISTORY "history [N] - muestra los últimos N (10) comandos escritos"
#define HELP_GETENV  "getenv var [var] - muestra valor de variable(s) de ambiente"
#define HELP_PID     "pid - muestra Process Id del minish"
#define HELP_SETENV  "setenv var valor - agrega o cambia valor de variable de ambiente"
#define HELP_STATUS  "status - muestra status de retorno de ultimo comando ejecutado"
#define HELP_UID     "uid - muestra nombre y número de usuario dueño del minish"
*/
