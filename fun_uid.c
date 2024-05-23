#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include "fun_uid.h"

int execute_uid(int argc, char **argv){
    __uid_t uid = getuid();
    printf("El UID del usuario actual es: %d\n", uid);
    struct passwd *user_entry = getpwuid(uid);
    if (user_entry != NULL) {
        printf("Nombre de usuario: %s\n", user_entry->pw_name);
    } else {
        printf("No se pudo obtener el nombre de usuario.\n");
        return 1;
    }
    return 0;
}