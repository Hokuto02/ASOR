#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[]){
    printf("PID %i\n", getpid());
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTSTP);
    int sigprocm;
    sigprocm = sigprocmask(SIG_BLOCK, &set, NULL);
    if(sigprocm == -1){
        perror("Error en sigprocmask ");
        return -1;
    }
    char *env = getenv("SLEEP_SECS");
    if(env == NULL){
        perror("Error en getenv ");
        return -1;
    }
    sleep(atoi(env));
    sigset_t setPend;
    sigemptyset(&setPend);
    int pending = sigpending(&setPend);
    if(pending == -1){
        perror("Error en sigpending ");
        return -1;
    }
    switch(sigismember(&setPend, SIGINT)){
        case -1:
            perror("Error en sigismember de SIGINT");
            return -1;
        break;
        case 1:
            printf("SIGINT se ha recibido durnte el tiempo dormido\n");
        break;
    }

    switch(sigismember(&setPend, SIGTSTP)){
        case -1:
            perror("Error en sigismember de SIGTSTP");
            return -1;
        break;
        case 1:
            printf("SIGTSTP se ha recibido durnte el tiempo dormido. Desbloqueando señal\n");
            sigdelset(&set, SIGINT);
            sigprocm = sigprocmask(SIG_UNBLOCK, &set, NULL);
            if(sigprocm == -1){
                perror("Error en sigprocmask ");
                return -1;
            }
        
        break;
    }

    return 0;
}