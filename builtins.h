int ejecutar (int argc, char **argv);

struct builtin_struct {
    char *cmd; // nombre del comando interno
    int (*func) (int, char **); // la función que lo ejecuta
    char *help_txt; // el texto de ayuda
};

struct builtin_struct *builtin_lookup(char *cmd);