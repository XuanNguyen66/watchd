#ifndef PARSE_H
#define PARSE_H

#define MAX_SERVICE 10
#define MAX_ARGV 20

typedef struct {
    pid_t pid;
    char name[64];
    char cmd[256];
    char *argv[MAX_ARGV];
} ServiceConfig;

typedef struct {
    ServiceConfig services[MAX_SERVICE];
    int total_services;
} SecWatchManager;


void parseline(char *line, SecWatchManager *manage);
void start_services(SecWatchManager *manage);

#endif
