#include <stdio.h>
#include <string.h>
#include <ctype.h>
void trim(){
    

}

int main(){
    char data[] = "  nginx=/usr";

    char *ptr_trim = data;

    int size_array = strlen(ptr_trim);

    for(int i = 0; i < size_array; i++){
            if(isspace((unsigned char)ptr_trim[i])){
                printf("O so %d la khoang trang!\n", i);
            }else {
                printf("O so %d la khoang trang!\n", i);
            }
    }

    printf("Chuỗi ban đâu: %s\n", data);

    char *ptr = strchr(data,'=');

    if( ptr != NULL){
        *ptr = '\0';

        printf("Sau khi parserline\n");
        printf("Key (Ten dich vu)  : %s\n", data);
        printf("Value (Lenh chay)  : %s\n", ptr + 1);
        printf("---------------------\n");
    } else {
        printf("Loi: Khong tim thay dau '=' trong chuoi!\n");
    }

    return 0;

}
