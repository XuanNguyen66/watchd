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
        exit(EXIT_FAILURE);
    }

    if(manage->state == SERVICE_RUNNING){
        int write_pid = open("./config/daemon_pid.txt", O_RDWR| O_CREAT | O_TRUNC, 0600);
        if(write_pid == -1){
            exit(EXIT_FAILURE);
        }
        dprintf(write_pid, "Service: [%s]\n", manage->services->name);
        dprintf(write_pid, "Pid: [%d]\n", manage->services->pid);
        close(write_pid);
    } 
}

void write_logging(SecWatchManager *manage){
    fprintf(stderr, "write_failed called\n");
    
    time_t now = time(NULL);
    struct tm *ts;
    char buf[80];

    ts = localtime(&now);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", ts);

    if(access("./logs", F_OK) != 0){
        perror("Check dir");
        exit(EXIT_FAILURE);
    }
    
    if(manage->state == SERVICE_RUNNING){
        int service_runningfd = open("./logs/log_services_running.log", O_RDWR| O_CREAT | O_APPEND, 0600);
        if(service_runningfd == -1){
            exit(EXIT_FAILURE);
        }
        dprintf(service_runningfd, "Service: [%s]\nTime: [%s]\n", manage->services->name, buf);
        dprintf(service_runningfd, "Pid: [%d]\n", manage->services->pid);
        dprintf(service_runningfd, "State: [%s]\n", state_name[manage->state]);
        close(service_runningfd);
    }

    if(manage->state == SERVICE_FAILED){
        int service_failedfd = open("./logs/log_services_failed.log", O_RDWR| O_CREAT | O_APPEND, 0600);
        if(service_failedfd == -1){
            exit(EXIT_FAILURE);
        }
        dprintf(service_failedfd, "Service: [%s]\nTime: [%s]\n", manage->services->name, buf);
        dprintf(service_failedfd, "Pid: [%d]\n", manage->services->pid);
        dprintf(service_failedfd, "State: [%s]\n", state_name[manage->state]);
        close(service_failedfd);
    }
}
