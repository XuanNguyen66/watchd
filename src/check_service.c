#include "parseline.h"


void restart_service(SecWatchManager *manage);
static void check_time(SecWatchManager *manage);

static bool is_process_alive(SecWatchManager *manage){
    while (waitpid(-1, NULL, WNOHANG) > 0);

    if (manage->services->pid > 0 && kill(manage->services->pid, 0) == 0)
    {
        return true;
    } 
    return false;
}

int check_service(SecWatchManager *manage){

    if (manage->state == SERVICE_FAILED){
        write_logging(manage);        
    }

    bool alive = is_process_alive(manage);
    if(manage->state != SERVICE_STARTING){
        if(alive){
            manage->state = SERVICE_RUNNING;
            write_logging(manage);
        }
        else{
            manage->state = SERVICE_STOPPED;
        }
    } else{
        if (!alive) {
            manage->state = SERVICE_STOPPED;
        }
    }

    switch(manage->state){
        case SERVICE_STARTING:
            break;
        case SERVICE_RUNNING:
            printf("Đây là services running\n");
            break;
        case SERVICE_STOPPED:
            printf("service tèo rồi\n");
            break;
        case SERVICE_FAILED:
            printf("CRITICAL: Service hỏng nặng, dừng thử lại!\n"); 
            break;
    }
    return manage->state;
}


void monitor_service(SecWatchManager *manage){
    check_time(manage);
    int current_state = check_service(manage);
    
    if (current_state == SERVICE_STOPPED) {
        restart_service(manage);
    }
}

void restart_service(SecWatchManager *manage){    

    if(manage->services->restart_count >= MAX_LIMIT){
        manage->state = SERVICE_FAILED;
        return;
    }

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
        manage->state = SERVICE_STARTING;

        // update time service restart
        manage->services->restart_time = time(NULL);
        manage->services->restart_count++;
        printf("Restart lần thứ %d cho service %s\n", 
               manage->services->restart_count, manage->services->name);
    }
}

static void check_time(SecWatchManager *manage){
    time_t now = time(NULL);
    if(manage->state == SERVICE_STARTING){
        double uptime = difftime( now, manage->services->restart_time);
        if(uptime >= 60.0){
            manage->state = SERVICE_RUNNING;
            manage->services->restart_count = 0;
            printf("Service đã chạy ổn định\n");
        } else{
            printf("Service chưa chạy ổn định\n");
        }
    }

}