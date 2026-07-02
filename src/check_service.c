#include "parseline.h"

static bool is_process_alive(SecWatchManager *manage){
    if (manage->services->pid > 0 && kill(manage->services->pid, 0) == 0)
    {
        return true;
    } 
    return false;
}

void check_service(SecWatchManager *manage){
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
}