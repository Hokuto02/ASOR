#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

volatile int contSIGINT = 0;
volatile int contSIGTSTP = 0;

void manejador(int signal){
    switch(signal){
        case SIGINT:
            contSIGINT++;
        break;
        case SIGTSTP:
            contSIGTSTP++;
        break;
    }

}

int main(int argc, char *argv[]){
    // SIGINT
    struct sigaction actSIGINT;
    if(sigaction(SIGINT, NULL, &actSIGINT) == -1){
        perror("Error en sigaction SIGINT, al sacar la accion");
        return -1;
    }
    actSIGINT.sa_handler = manejador;
    if(sigaction(SIGINT, &actSIGINT, NULL) == -1){
        perror("Error en sigaction SIGINT, al poner la accion");
        return -1;
    }
    // SIGTSTP
    struct sigaction actSIGTSTP;
    if(sigaction(SIGTSTP, NULL, &actSIGTSTP) == -1){
        perror("Error en sigaction SIGTSTP, al sacar la accion");
        return -1;
    }
    actSIGINT.sa_handler = manejador;
    if(sigaction(SIGTSTP, &actSIGINT, NULL) == -1){
        perror("Error en sigaction SIGTSTP, al poner la accion");
        return -1;
    }

    sigset_t mask;
    sigemptyset(&mask);
    while(contSIGINT + contSIGTSTP < 10){
        sigsuspend(&mask);
    }

    printf("Se ha recibido la señal SIGINT %i veces\n", contSIGINT);
    printf("Se ha recibido la señal SIGTSTP %i veces\n", contSIGTSTP);

    return 0;
}