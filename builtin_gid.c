#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int execute_gid(int argc, char **argv) {
    if(argc = 1){
        // Obtener el GID principal
        gid_t gid = getgid();
        printf("El GID del grupo principal es: %d\n", gid);

        // Obtener el número de grupos secundarios
        int ngroups = getgroups(0, NULL);
        if (ngroups == -1) {
            perror("getgroups");
            return 1;
        }

        // Reservar memoria para los grupos secundarios
        gid_t *groups = malloc(ngroups * sizeof(gid_t));
        if (groups == NULL) {
            perror("malloc");
            return 1;
        }

        // Obtener los grupos secundarios
        ngroups = getgroups(ngroups, groups);
        if (ngroups == -1) {
            perror("getgroups");
            free(groups);
            return 1;
        }

        // Imprimir los GIDs de los grupos secundarios
        printf("El GID de los grupos secundarios son: ");
        for (int i = 0; i < ngroups; i++) {
            printf("%d ", groups[i]);
        }
        printf("\n");

        // Liberar memoria
        free(groups);

        return 0;
    }else{
        printf("Gid no lleva argumentos");
        return 1;
    }
}