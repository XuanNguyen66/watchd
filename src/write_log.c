#include "parseline.h"

const char *state_name[] = {
    "STARTING",
    "RUNNING",
    "STOPPED",
    "FAILED"
};

void write_pid_file(SecWatchManager *manage){
    if(access("./config", F_OK) != 0){
        perror("Check dir");
       return;
    }
    int write_pid = open("./config/daemon_pid.txt", O_RDWR| O_CREAT | O_TRUNC, 0600);
    if(write_pid == -1){
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < manage->total_services; i++){
        ServiceConfig *s = &manage->services[i];
        if(s->state == SERVICE_RUNNING){
            dprintf(write_pid, "Service: [%s]\n", s->name);
            dprintf(write_pid, "Pid: [%d]\n", s->pid);
        } 
    }
    close(write_pid);
    
}

void write_logging(ServiceConfig *s){
    fprintf(stderr, "write_failed called\n");
    
    time_t now = time(NULL);
    struct tm *ts;
    char buf[80];

    ts = localtime(&now);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", ts);

    if(access("./logs", F_OK) != 0){
        perror("Check dir");
        return;
    }
    
    if(s->state == SERVICE_RUNNING){
        int service_runningfd = open("./logs/log_services_running.log", O_RDWR| O_CREAT | O_APPEND, 0600);
        if(service_runningfd == -1){
           return;
        }
        dprintf(service_runningfd, "Service: [%s]\nTime: [%s]\n", s->name, buf);
        dprintf(service_runningfd, "Pid: [%d]\n", s->pid);
        dprintf(service_runningfd, "State: [%s]\n", state_name[s->state]);
        close(service_runningfd);
    }

    if(s->state == SERVICE_FAILED){
        int service_failedfd = open("./logs/log_services_failed.log", O_RDWR| O_CREAT | O_APPEND, 0600);
        if(service_failedfd == -1){
            return;
        }
        dprintf(service_failedfd, "Service: [%s]\nTime: [%s]\n", s->name, buf);
        dprintf(service_failedfd, "Pid: [%d]\n", s->pid);
        dprintf(service_failedfd, "State: [%s]\n", state_name[s->state]);
        close(service_failedfd);
    }
}
