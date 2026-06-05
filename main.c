#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

volatile sig_atomic_t shutting_down = 0;
pid_t child_pid = -1;

void sigchld_handler(int sig){
    if (shutting_down) {
        return; 
    }
    int  olderrno =  errno;
    pid_t repid;
    int status;
   
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,SIGCHLD);

    while ((repid = waitpid(-1,NULL,WNOHANG)) > 0){
        char *msg_clear = "Clear service success, rester service...\n";
        write(STDOUT_FILENO, msg_clear, strlen(msg_clear));
        pid_t new_pid = fork();
        if(new_pid < 0){
            char *msg_err_fork = "Fork that bai\n";
            write(STDOUT_FILENO, msg_err_fork, strlen(msg_err_fork));
        }else if(new_pid > 0){
            child_pid = new_pid;
            char *msg_err_fork2 = "Khởi động dịch vụ thành công\n";
            write(STDOUT_FILENO, msg_err_fork2, strlen(msg_err_fork2));
        }else if(new_pid == 0){
            sigprocmask(SIG_UNBLOCK, &mask, NULL);

            if (execlp("sleep", "sleep", "10", NULL) == -1) {
                char *msg_err_exec = "Loi khi chay dich vu\n";
                write(STDOUT_FILENO, msg_err_exec, strlen(msg_err_exec));
                _exit(1);
        }

    }
    }
    errno = olderrno;
}

void sigint_handler(int sig){
    shutting_down = 1;
    int olderrno = errno;
    char *msg = "\n[SecWatch] Nhan lenh tat. Dang gui SIGTERM...\n";
    write(STDOUT_FILENO, msg, strlen(msg));
    
    if(child_pid > 0){
        kill(child_pid, SIGTERM);
    }
    while (waitpid(-1,NULL, 0) > 0);
    char *msg_clear = "[SecWatch] Da don dep sach he thong. Goodbye!\n";
    write(STDOUT_FILENO, msg_clear, strlen(msg_clear));
    errno = olderrno;
    _exit(0);
}

void become_daemon(){
    pid_t pid;
    
    pid = fork();

    if(pid < 0) exit(1);
    if(pid > 0){
        printf("Parent có child là: %d\n", pid);
        exit(0);
    }
    
    // child use setsid = session leader
    if(setsid() < 0) exit(1);

    pid = fork();
    if (pid < 0) exit(1);
    // kill child
    if (pid > 0) {
        printf("Child có childhood là: %d\n", pid);
        exit(0);
    }

    int fd = open("/var/log/secwatch.log", O_WRONLY | O_CREAT | O_APPEND, 0644);

    if(fd != -1){
        dup2(fd, 1);
        dup2(fd, 2);
        close(fd);
        
        // off buffer -> write real-time
        setvbuf(stdout, NULL, _IONBF, 0);
        setvbuf(stderr, NULL, _IONBF, 0);
    }else{
        perror("Không thể mở file log secwatch.log");
    }

}



int main(){
    become_daemon();

    pid_t pid;
    int status;
    struct sigaction sa_chld, sa_int;

    sa_int.sa_handler = sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sigaddset(&sa_int.sa_mask, SIGCHLD);
    sa_int.sa_flags = 0;

    if(sigaction(SIGINT, &sa_int, NULL) == -1){
        perror("sigint error");
        exit(1);
    }
    

    sa_chld.sa_handler = sigchld_handler;    
    sigemptyset(&sa_chld.sa_mask);
    sa_chld.sa_flags = SA_RESTART;

    if(sigaction(SIGCHLD, &sa_chld,NULL) == -1){
          perror("signal error");
          exit(1);
    }

    sigset_t mask, prev_mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);

    sigprocmask(SIG_BLOCK, &mask, &prev_mask); 
        if((pid = fork()) < 0){
            printf("Fork Failed");
            exit(1);
     } else if((pid == 0)){
          sigprocmask(SIG_UNBLOCK,&mask, NULL);
          
          if(execlp("sleep","sleep","300", NULL) == -1){
               perror("Services was running wrong");
               exit(1);
          }
      }else {
          child_pid = pid;
          printf("\n[secwatch] dịch vụ con đang chạy với pid: %d\n", pid);
      } 
   sigprocmask(SIG_SETMASK, &prev_mask, NULL);

    while(1){
        pause();
    }
       
    return 0;

}

