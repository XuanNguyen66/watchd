#include "parseline.h"

void start_services(SecWatchManager *manage){
    pid_t pid;
    int i;
    for(i = 0; i < manage->total_services; i++){
        pid = fork();

        if(pid < 0){
            printf("fork failed for service %s\n", manage->services[i].name);
            continue;
        }   

        if(pid == 0){
            printf("Cmdline %s\n", manage->services[i].argv[0]);
            if(execvp(manage->services[i].argv[0], manage->services[i].argv) == -1){
                perror("execvp failed");
                exit(1);
            }
        }
        if(pid > 0){
            manage->services[i].pid = pid;
            printf("Tôi đang quản lý các services là: %s\n", manage->services[i].name);
        }
    }

}
