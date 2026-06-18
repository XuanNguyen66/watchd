#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trim.h"
#include "parseline.h"

void parseline(char *line, SecWatchManager *manage){
    
    char *ptr = strchr(line, '=');
    
    int idx = 0;

    if(ptr != NULL){
        *ptr = '\0';
        char *key = line;
        char *value = ptr + 1;
        trimline(key);
        trimline(value);
        printf("%s\n", key);
        printf("%s\n", value);

        if(strcmp(key, "name") == 0){
            idx = manage->total_services;
            strcpy(manage->services[idx].name, value);
        }


        if(strcmp(key, "cmd") == 0){
           idx = manage->total_services;

           strcpy(manage->services[idx].cmd,value);
           manage->total_services++;
        }
    }
}
