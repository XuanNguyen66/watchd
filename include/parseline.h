#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <time.h>

#define MAX_SERVICE 10
#define MAX_ARGV 20
#define MAX_LIMIT 0

typedef enum {
    SERVICE_STARTING,
    SERVICE_RUNNING,
    SERVICE_STOPPED,
    SERVICE_FAILED,
} ServiceState;

typedef struct {
    pid_t pid;
    char name[64];
    char cmd[256];
    char *argv[MAX_ARGV];

    int restart_limit;
    unsigned int restart_count;
    time_t restart_time;
    time_t service_recover;

    ServiceState state;
    ServiceState old_state;
    
} ServiceConfig;

typedef struct {
    ServiceConfig services[MAX_SERVICE];
    int total_services;
} SecWatchManager;


void parseline(char *line, SecWatchManager *manage);
void start_services(SecWatchManager *manage);
int check_service(ServiceConfig *s);
void monitor_service(SecWatchManager *manage);
void write_logging(ServiceConfig *s);
void check_time(SecWatchManager *manage);
void write_pid_file(ServiceConfig *s);

#endif
