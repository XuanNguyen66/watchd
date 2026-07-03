#include "parseline.h"


void restart_service(SecWatchManager *manage);

static bool is_process_alive(SecWatchManager *manage){
    if (manage->services->pid > 0 && kill(manage->services->pid, 0) == 0)
    {
        return true;
    } 
    return false;
}

int check_service(SecWatchManager *manage){
    if(is_process_alive(manage)){
        manage->state = SERVICE_RUNNING;
    }
    else{
        manage->state = SERVICE_STOPPED;
    }

    switch(manage->state){
        case SERVICE_RUNNING:
            printf("Đây là services running\n");
            break;
        case SERVICE_STOPPED:
            printf("service tèo rồi\n");
            break;
    }
    return manage->state;
}


void monitor_service(SecWatchManager *manage){
    if(check_service(manage) == SERVICE_STOPPED){
       restart_service(manage);
    }
}

void restart_service(SecWatchManager *manage){
    pid_t new_pid = fork();

    if (new_pid < 0) {
        printf("fork failed for service %s\n", manage->services->name);
        return;
    }

    if (new_pid == 0)
    {
       if (execvp(manage->services->argv[0], manage->services->argv) == -1) {
            perror("execvp failed");
            exit(1);
        }
    } else {
        manage->services->pid = new_pid;
        manage->state = SERVICE_RUNNING;
    }
}