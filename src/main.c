#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <parseline.h>


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
    fclose(fd);

    printf("Dịch vụ đầu tiên là: %s\n có cmdline là: %s\n", manage.services[0].name, manage.services[0].cmd);
   
    printf("Dịch vụ thứ hai là: %s\n có cmdline là: %s\n", manage.services[1].name, manage.services[1].cmd);
    //printf("Dịch vụ thứ 2 là: %s\n", my_manager.services[0].cmd);
    //become_daemon();

    pid_t pid;
    int i;
    
    for(i = 0; i < manage.total_services; i++){
        if((pid = fork()) < 0){
            printf("Fork Failed");
            exit(1);
        }else if((pid == 0)){
                    
          char *custom_argv[10];
          int arg_idx = 0;   
          char cmd_tmp[256];
          strcpy(cmd_tmp, manage.services[i].cmd); 

          char *token = strtok(cmd_tmp, " ");
          while (token != NULL && arg_idx < 9) {
              custom_argv[arg_idx++] = token;
              token = strtok(NULL, " ");
          }
          custom_argv[arg_idx] = NULL;
          if(execvp(custom_argv[0], custom_argv)== -1){
               perror("Services was running wrong");
               exit(1);
        }
        }else {
          manage.services[i].pid = pid;
          //printf("\n[secwatch] dịch vụ con đang chạy với pid: %d\n", pid);
          printf("\n[secwatch] dich vu %s dang chay voi pid: %d\n",
               manage.services[i].name, pid);
          printf("có cmdline là: \"%s\"\n", manage.services[i].cmd);
      }
    }   
 
    while(1){
        pause();
    }
       
    return 0;
}

