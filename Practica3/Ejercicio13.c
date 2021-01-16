#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

volatile int borra = 0;
volatile int alarma = 0;

void manejador(int signal){
    switch(signal){
        case SIGUSR1:
            borra = 1;
        break;
        case SIGALRM:
            alarma = 1;
        break;
    }
}

int main(int argc, char *argv[]) {

    printf("%i\n", getpid());

    // SIGUSR1
    struct sigaction actSIGUSR1;
    if(sigaction(SIGUSR1, NULL, &actSIGUSR1) == -1){
        perror("Error en sigaction SIGUSR1, al sacar la accion");
        return -1;
    }
    actSIGUSR1.sa_handler = manejador;
    if(sigaction(SIGUSR1, &actSIGUSR1, NULL) == -1){
        perror("Error en sigaction SIGUSR1, al poner la accion");
        return -1;
    }

    // SIGALRM
    struct sigaction actSIGALRM;
    if(sigaction(SIGALRM, NULL, &actSIGALRM) == -1){
        perror("Error en sigaction SIGALRM, al sacar la accion");
        return -1;
    }
    actSIGALRM.sa_handler = manejador;
    if(sigaction(SIGALRM, &actSIGALRM, NULL) == -1){
        perror("Error en sigaction SIGALRM, al poner la accion");
        return -1;
    }


    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGUSR1);
    sigdelset(&mask, SIGALRM);

    alarm(atoi(argv[1]));

    sigsuspend(&mask);
    
    if(borra == 0 && alarma == 1){
        printf("Borrado");
        unlink(argv[0]);
    }
    
	return 0;
}