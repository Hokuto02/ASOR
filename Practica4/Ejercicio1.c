#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]){
    pid_t pid;
    int fd[2];
    int pi = pipe(fd);
    if(pi==-1){
        perror("Error pipie ");
        return-1;
    }
    pid = fork();
    switch(pid){
        case -1: //ERROR
            perror("Error fork ");
            return-1;
        case 0: //HIJO
            dup2(fd[0], 0);
            close(fd[0]);
            close(fd[1]);
            int exH;
            exH = execlp(argv[3], argv[3], argv[4], NULL);
            if(exH == -1){
                perror("Error execlp hijo ");
                return-1;
            }
        break;
        default: //PADRE
            dup2(fd[1], 1);
            close(fd[0]);
            close(fd[1]);
            int exP;
            exP = execlp(argv[1], argv[1], argv[2],NULL);
            if(exP == -1){
                perror("Error execlp padre ");
                return-1;
            }
        break;
    }
    return 0;
}