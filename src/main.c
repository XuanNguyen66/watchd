#include "parseline.h"
#include "become_daemon.h"


int main(){
    SecWatchManager manage;
    manage.total_services = 0;

    FILE *fd = fopen("secwatch.conf", "r");

    char line[256];

    if(fd == NULL){
        printf("Open file error\n");
        return 1;
    }
    while(fgets(line, sizeof(line), fd) != NULL){
       parseline(line, &manage);
    }
    start_services(&manage);
    
    while(1){
        while (waitpid(-1, NULL, WNOHANG) > 0);
        check_service(&manage);
        monitor_service(&manage);
        sleep(5);
    }

    printf("Số lượng dịch vụ đã parse: %d\n", manage.total_services);
    for (int i = 0; i < manage.total_services; i++) {
        printf("Dịch vụ %d: %s | Lệnh: %s\n", 
               i + 1, manage.services[i].name, manage.services[i].cmd);
    }

    return 0;
}

