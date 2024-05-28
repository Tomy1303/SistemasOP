#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

int execute_dir(int argc, char **argv){
    if(argc<=2){
        char *este_dir = getcwd(NULL,0);
        char *palabra = argv[1];
        DIR *dir = opendir(este_dir);
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if(palabra != NULL){
                if(strstr(entry->d_name, palabra) != NULL){
                     printf("%s\n", entry->d_name);
                }
            }else{
                 printf("%s\n", entry->d_name);
            }
        }
    }
}