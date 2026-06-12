#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void parseline(char *line){
    char *token = strtok(line, "=\n");
    while(token != NULL){
        printf("Token: %s\n", token);
        token = strtok(NULL, "=\n");
    }
}
    
int main(){
   FILE *fd = fopen("../secwatch.conf", "r");

   if(fd == NULL){
        printf("Erro");
        return 0;
   }

   char line[10];
   while(fgets(line, sizeof(line),fd) != NULL){
   //     printf("%s", line);
        parseline(line);
   }
   fclose(fd);

   return 0;
}
