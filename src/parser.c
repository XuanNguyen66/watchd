#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trim.h"
#include "parseline.h"

void parseline(char *line){
    char *ptr = strchr(line, '=');
  
    if(ptr != NULL){
        *ptr = '\0';
        char *key = line;
        char *value = ptr + 1;
        trimline(key);
        trimline(value);
        printf("%s\n", key);
        printf("%s\n", value);
    }
}
    
//int main(){
//   FILE *fd = fopen("secwatch.conf", "r");

//   if(fd == NULL){
//        printf("--------------\n");
//        printf("Erro\n");
//        return 0;
//   }
//
//   char line[256];
//   while(fgets(line, sizeof(line),fd) != NULL){
//        printf("%s", line);
//        parseline(line);
//   }
//   fclose(fd);

//   return 0;
//}
