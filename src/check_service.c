#include "parseline.h"


void restart_service(ServiceConfig *s);
void check_time(SecWatchManager *manage);

static bool is_process_alive(ServiceConfig *s){
    
    if (s->pid > 0 && kill(s->pid, 0) == 0)
    {
        return true;
    } 
    return false;
}

int check_service(ServiceConfig *s){

    if (s->state == SERVICE_FAILED){
       return s->state;
    }

    bool alive = is_process_alive(s);
    if(s->state != SERVICE_STARTING){
        if(alive){
            s->state = SERVICE_RUNNING;
        }
        else{
            s->state = SERVICE_STOPPED;
        }
    } else{
        if (!alive) {
            s->state = SERVICE_STOPPED;
        }
    }
    return s->state;
}


void monitor_service(SecWatchManager *manage){
    while (waitpid(-1, NULL, WNOHANG) > 0);

    check_time(manage);

    for (int i = 0; i < manage->total_services; i++) {
        ServiceConfig *s = &manage->services[i];
        
        check_service(s);
        
        if (s->state != s->old_state){
            write_logging(s);
            s->old_state = s->state;
        }
        if (s->state == SERVICE_STOPPED){
            restart_service(s);
            s->old_state = s->state;
        }
    }
}

void restart_service(ServiceConfig *s){    

    if( s->restart_count >= MAX_LIMIT){
        s->state = SERVICE_FAILED;
        return;
    }

    pid_t new_pid = fork();

    if (new_pid < 0) {
        printf("fork failed for service %s\n", s->name);
        return;
    }

    if (new_pid == 0)
    {
       if (execvp(s->argv[0], s->argv) == -1) {
            perror("execvp failed");
            exit(1);
        }
    } else {
        s->pid = new_pid;
        s->state = SERVICE_STARTING;

        // update time service restart
        s->restart_time = time(NULL);
        s->restart_count++;
    }
}

void check_time(SecWatchManager *manage){
    int i;
    time_t now = time(NULL);
    for(i = 0; i < manage->total_services; i++){

        ServiceConfig *s = &manage->services[i];

        if(s->state == SERVICE_STARTING){
        double uptime = difftime( now, s->restart_time);
        if(uptime >= 60.0){
            s->state = SERVICE_RUNNING;
            s->restart_count = 0;
            write_pid_file(s);
        }
    }
    }

}