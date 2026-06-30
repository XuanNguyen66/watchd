#include "parseline.h"

// bool is_process_alive(){
//     if (kill(, 0) == 0)
//     {
//         return 0;
//     }
//     if(kill(-pid,0) )
    
//     return 1;
// }

void check_service(SecWatchManager *manage){
    if(manage->services->pid){
        manage->state = SERVICE_RUNNING;
    }
    else{
        manage->state = SERVICE_STOPPED;
    }

    switch(manage->state){
        case SERVICE_RUNNING:
            printf("Đây là services running");
            break;
        case SERVICE_STOPPED:
            break;
    }

}