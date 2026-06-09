#include <stdio.h>
#include <stdlib.h>


int main(){
   FILE *file = fopen("secwatch.conf", "r");
   
   char line[100];

   if(file == NULL){
        perror("Error opening file");
        exit(0);
   }
   while(fgets(line, sizeof(line), file)){
        printf("%s", line);
   }

   fclose(file);

    return 0;
}
