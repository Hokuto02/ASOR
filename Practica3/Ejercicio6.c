#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

int info(char *p){
    pid_t pid;
    pid = getpid();
    printf("%s PID del proceso %i\n", p, pid);
    printf("%s PID proceso padre %i\n", p, getppid());
    printf("%s GID del proceso %i\n", p, getpgid(pid));
    printf("%s SID del proceso %i\n", p, getsid(pid));

    int lim;
    struct rlimit rlim;
    lim = getrlimit(RLIMIT_NOFILE, &rlim);
    if(lim == -1){
        perror("Error getrlimit ");
        return -1;
    }
    printf("%s Numero maximo de ficheros que puede abrir el ficheros: %i\n", p, rlim.rlim_max);
    
    char *buf=(char *)malloc(100*sizeof(char));
    if(getcwd(buf, 100) == NULL){
        perror("Error getcwd ");
        return -1;
    }
    printf("%s DIR actual: %s\n", p, buf);
    free(buf);
}

int main(int argc, char *argv[]){
    switch(fork()){
        case -1: //Error
            perror("Error fork ");
            return -1;
        break;
        case 0: //Hijo
            sleep(2);
            setsid();
            int dir;
            dir = chdir("./tmp");
            if(dir == -1){
                perror("Error chdir ");
                return -1;
            }
            if(info("Hijo") == -1){
                perror("Error info ");
                return -1;
            }
        break;
        default: //Padre
            if(info("Padre") == -1){
                perror("Error info ");
                return -1;
            }
        break;
    }
    return 0;
}