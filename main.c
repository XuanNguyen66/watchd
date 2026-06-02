#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void signal_handler(int sig){
    write(STDOUT_FILENO, "=> DA BAT DUOC SIGCHLD!\n", 24);
    pid_t repid;
    int status;
    
    while ((repid = waitpid(-1,NULL,WNOHANG)) > 0){
        char *msg_clear = "Clear service success, rester service...\n";
        write(STDOUT_FILENO, msg_clear, strlen(msg_clear));

        pid_t new_pid = fork();
        if(new_pid < 0){
            char *msg_err_fork = "Fork that bai\n";
            write(STDOUT_FILENO, msg_err_fork, strlen(msg_err_fork));
        }else if(new_pid > 0){
            char *msg_err_fork2 = "Khởi động dịch vụ thành công\n";
            write(STDOUT_FILENO, msg_err_fork2, strlen(msg_err_fork2));
        }else if(new_pid == 0){
            if (execlp("sleep", "sleep", "10", NULL) == -1) {
                char *msg_err_exec = "Loi khi chay dich vu\n";
                write(STDOUT_FILENO, msg_err_exec, strlen(msg_err_exec));
                _exit(1);
        }

    }
    
    }
}

int main(){
    pid_t pid;
    int status;
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = signal_handler;
    
    if(sigaction(SIGCHLD, &sa,NULL) == -1){
        perror("signal error");
        exit(1);
    }
    if((pid = fork()) < 0){
        printf("Fork Failed");
        exit(1);
    } else if((pid == 0)){
        if(execlp("sleep","sleep","300", NULL) == -1){
            perror("Services was running wrong");
            exit(1);
        }
    }else {
        printf("[secwatch] dịch vụ con đang chạy với pid: %d\n", pid);
    } 

    while(1){
        pause();
    }
       
    return 0;

}
