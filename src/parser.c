#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trim.h"
#include "parseline.h"

void parseline(char *line, SecWatchManager *manage){
    trimline(line);
    if (strcmp(line, "[service]") == 0){
        if(manage->total_services >= MAX_SERVICE){
           printf("[WARNING]: Please checking toltal services -> (Max: %d)\n", MAX_SERVICE);
            return;
        }
        manage->total_services++;
        return;
    }
    char *delimiter = strchr(line, '=');
    if (delimiter != NULL) {
        *delimiter = '\0';
        char *key = line;
        char *value = delimiter + 1; 
        trimline(key);
        trimline(value);
        printf("%s\n", key);
        printf("%s\n", value);
        int idx = manage->total_services - 1;
        if(strcmp(key,"name") == 0){
            strcpy(manage->services[idx].name, value);
        }
        if(strcmp(key,"cmd") == 0){
            strcpy(manage->services[idx].cmd, value);

        int argc = 0;
        char *token = strtok(manage->services[idx].cmd, " ");

        while(token != NULL && argc < MAX_ARGV -1){
            manage->services[idx].argv[argc] = token;
            printf("Chuỗi sau khi token: %s\n", token);
            argc++;
            token = strtok(NULL," ");
        }
            manage->services[idx].argv[argc] = NULL;
        }
    }

}
