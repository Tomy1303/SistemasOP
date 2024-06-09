#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include "builtin_uid.h"

// Función para ejecutar el comando uid
int execute_uid(int argc, char **argv) {
    // Obtener el UID del usuario actual
    __uid_t uid = getuid();
    // Imprimir el UID del usuario actual
    printf("El UID del usuario actual es: %d\n", uid);

    // Obtener la entrada del usuario en la base de datos de contraseñas usando el UID
    struct passwd *user_entry = getpwuid(uid);

    // Verificar si se pudo obtener la entrada del usuario
    if (user_entry != NULL) {
        // Imprimir el nombre de usuario
        printf("Nombre de usuario: %s\n", user_entry->pw_name);
    } else {
        // Si no se pudo obtener el nombre de usuario, imprimir un mensaje de error
        printf("No se pudo obtener el nombre de usuario.\n");
        return 1; // Retornar 1 para indicar que hubo un error
    }

    return 0; // Retornar 0 para indicar que la función se ejecutó correctamente
}