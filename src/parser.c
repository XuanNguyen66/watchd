#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trim.h"
#include "parseline.h"

void parseline(char *line, SecWatchManager *manage){
    trimline(line);

    if (line[0] == '\0' || line[0] == '#') {
        return;
    }

    if (strcmp(line, "[service]") == 0){
        if(manage->total_services >= MAX_SERVICE){
           printf("[WARNING]: Please checking toltal services -> (Max: %d)\n", MAX_SERVICE);
            return;
        }

        ServiceConfig *new_service = &manage->services[manage->total_services];
        memset(new_service, 0, sizeof(ServiceConfig));

        new_service->restart_limit = MAX_LIMIT;

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
        int idx = manage->total_services - 1;

        if (idx < 0) {
            printf("[WARNING]: Key '%s' found before any [service] section. Ignored.\n", key);
            return;
        }

        ServiceConfig *s = &manage->services[idx];

        if(strcmp(key,"name") == 0){
            strcpy(s->name, value);
        }
        if(strcmp(key,"cmd") == 0){
            strcpy(s->cmd, value);

        int argc = 0;

        char *token = strtok(s->cmd, " ");

        while(token != NULL && argc < MAX_ARGV -1){
            s->argv[argc] = token;
            argc++;
            token = strtok(NULL," ");
        }
            s->argv[argc] = NULL;
        }
    }

}
