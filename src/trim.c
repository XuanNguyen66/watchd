#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "trim.h"

void trimline(char *str){
     if (str == NULL)
         return;
     int len = strlen(str);
     if(len == 0)
         return;
     int end = len - 1;
     while(end >= 0 && isspace((unsigned char)str[end])){
        end--;
     }
     str[end + 1] = '\0';

     int start = 0;
     while(str[start] != '\0' && isspace((unsigned char)str[start])){
        start++;
     }

     if(start > 0){
        int i = 0;
        while(str[start + i] != '\0'){
            str[i] = str[start + i];
            i++;
        }
        str[i] = '\0';
     }
}

