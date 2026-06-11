#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void trim(char *str){
    // Find the space on the right
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])){
        len--;
    }
    str[len] = '\0';
    
    //Find the space on the left
    int start = 0;
    while(str[start] != '\0' && isspace((unsigned char) str[start])){
        start++;
    }
    if(start > 0){
        memmove(str, str + start, len - start + 1);
    }
}



int main(){
   FILE *file = fopen("secwatch.conf", "r");
   
   char line[100];

   if(file == NULL){
        perror("Error opening file");
        exit(0);
   }
  // int line_num = 0;

   while(fgets(line, sizeof(line), file) != NULL){
    //    line_num++;
        trim(line);
        printf("%s\n", line);
   }

   fclose(file);

    return 0;
}
