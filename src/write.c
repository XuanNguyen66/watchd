#include "parseline.h"

void write_failed(SecWatchManager *manage){
    fprintf(stderr, "write_failed called\n");
    
    time_t now = time(NULL);
    struct tm *ts;
    char buf[80];

    ts = localtime(&now);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", ts);

    if( access("./log", F_OK) != 0){
        perror("Check dir");
        exit(EXIT_FAILURE);
    }
    
    int service_failedfd = open("./log/log_services_failed.log", O_RDWR| O_CREAT | O_APPEND, 0600);
    if(service_failedfd == -1){
        exit(EXIT_FAILURE);
    }
    dprintf(service_failedfd, " Sucess: Service: [%s]\nTime failed: [%s]\n", manage->services->name, buf);
    close(service_failedfd);
}