#include <stdio.h>
#include <unistd.h>

void become_daemon(){
    pid_pid;
    
    pid = fork();

    if(pid < 0){
        exit(1);
    }
    if(pid > 0){
        exit(0)
    }

    // child use setsid = session leader
    if(setsid() < 0){
        exit(1);
    }
    pid = fork()

    pid(pid < 0){
        exit(1);
    }
    
    
}
