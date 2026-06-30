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

#define MAX_SERVICE 10
#define MAX_ARGV 20

typedef struct {
    pid_t pid;
    char name[64];
    char cmd[256];
    char *argv[MAX_ARGV];
} ServiceConfig;

typedef enum {
    SERVICE_RUNNING,
    SERVICE_STOPPED,
} ServiceState;

typedef struct {
    ServiceConfig services[MAX_SERVICE];
    ServiceState state;
    int total_services;
} SecWatchManager;


void parseline(char *line, SecWatchManager *manage);
void start_services(SecWatchManager *manage);
void check_service(SecWatchManager *manage);

#endif
