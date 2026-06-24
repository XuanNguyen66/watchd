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
            printf("Cảnh báo: Đã đạt giới hạn tối đa (%d). Bỏ qua dịch vụ thừa!\n", MAX_SERVICE);
            return;
        }
        printf("đã vào services\n");
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
        }
    }
}
