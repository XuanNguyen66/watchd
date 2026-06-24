#ifndef PARSE_H
#define PARSE_H

#define MAX_SERVICE 1

typedef struct {
    pid_t pid;
    char name[64];
    char cmd[256];
} ServiceConfig;

typedef struct {
    ServiceConfig services[MAX_SERVICE];
    int total_services;
} SecWatchManager;


void parseline(char *line, SecWatchManager *manage);

#endif
