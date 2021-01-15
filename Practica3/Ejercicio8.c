#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

    switch(fork()){
        case -1: //Error
            perror("Error fork ");
            return -1;
        break;
        case 0: //Hijo
            setsid();
            printf("Hijo con PID %i\n", getpid());
            sleep(2);
            int fdout, fderr, fdnull;
            fdout =  open("/tmp/daemon.out", O_RDWR | O_CREAT | O_TRUNC, 00777);
            fderr =  open("/tmp/daemon.err", O_RDWR | O_CREAT | O_TRUNC, 00777);
            fdnull =  open("/dev/null", O_RDWR , 00777);
            if(fdout == -1 || fderr == -1 || fdnull == -1){
                perror("Error en open ");
                return -1;
            }
            int fd0, fd1, fd2;
            fd0 = dup2(fdnull, 0);
            close(fdnull);
            fd1 = dup2(fdout, 1);
            close(fdout);
            fd2 = dup2(fderr, 2);
            close(fderr);
            if(fd0 == -1 || fd1 == -1 || fd2 == -1){
                perror("Error en dup2 ");
                return -1;
            }   

            int ex;
            ex = execvp(argv[1], argv + 1);
            if(ex == -1){
                perror("Error en execvp ");
                return -1;
            }
        break;
        default: //Padre
            printf("Padre con PID %i\n", getpid());
        break;
    }
    return 0;
}