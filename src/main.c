#include "parseline.h"
#include "become_daemon.h"


int main(){

    if(become_daemon(01) < 0){
        fprintf(stderr, "Init daemon failed!\n");
        return 1;
    }

    SecWatchManager manage;
    memset(&manage, 0, sizeof(SecWatchManager));

    manage.total_services = 0;

    FILE *fd = fopen("./config/watch.conf", "r");

    char line[256];

    if(fd == NULL){
        printf("Open file error\n");
        return 1;
    }
    while(fgets(line, sizeof(line), fd) != NULL){
       parseline(line, &manage);
    }
    fclose(fd);
    
    start_services(&manage);
    
    while(1){
        monitor_service(&manage);
        sleep(5);
    }
    return 0;
}

