#ifndef PARSE_H
#define PARSE_H


typedef struct {
    pid_t pid;
    char name[64];
    char cmd[256];
} ServiceConfig;

typedef struct {
    ServiceConfig services[10];
    int total_services;
} SecWatchManager;


void parseline(char *line, SecWatchManager *manage);

#endif
