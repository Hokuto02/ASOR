#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    pid_t pid;
    pid = getpid();
    printf("PID del proceso %i\n", pid);
    printf("PID proceso padre %i\n", getppid());
    printf("GID del proceso %i\n", getpgid(pid));
    printf("SID del proceso %i\n", getsid(pid));

    int lim;
    struct rlimit rlim;
    lim = getrlimit(RLIMIT_NOFILE, &rlim);
    if(lim == -1){
        perror("Error getrlimit ");
        return -1;
    }
    printf("Numero maximo de ficheros que puede abrir el fichero", rlim.rlim_max);
    
    char *buf=(char *)malloc(100*sizeof(char));
    if(getcwd(buf, 100) == NULL){
        perror("Error getcwd ");
        return -1;
    }
    printf("DIR actual: %s\n", buf);
    free(buf);
    return 0;
}