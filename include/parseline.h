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

typedef struct {
    pid_t pid;
    char name[64];
    char cmd[256];
    char *argv[MAX_ARGV];

    int restart_limit[MAX_LIMIT];
    unsigned int restart_count;
    time_t restart_time;
    time_t service_recover;
    
} ServiceConfig;

typedef enum {
    SERVICE_STARTING,
    SERVICE_RUNNING,
    SERVICE_STOPPED,
    SERVICE_FAILED,
} ServiceState;

typedef struct {
    ServiceConfig services[MAX_SERVICE];
    ServiceState state;
    int total_services;
} SecWatchManager;


void parseline(char *line, SecWatchManager *manage);
void start_services(SecWatchManager *manage);
int check_service(SecWatchManager *manage);
void monitor_service(SecWatchManager *manage);
void write_logging(SecWatchManager *manage);
void check_time(SecWatchManager *manage);
void write_pid_file(SecWatchManager *manage);

#endif
