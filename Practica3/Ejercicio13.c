#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    printf("%i\n", getpid());

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigprocmask(SIG_BLOCK, &set, NULL);

    sleep(atoi(argv[1]));

    sigset_t setPend;
    sigemptyset(&setPend);
    int pending = sigpending(&setPend);
    if(pending == -1){
        perror("Error en sigpending ");
        return -1;
    }
    switch(sigismember(&setPend, SIGUSR1)){
        case -1:
            perror("Error en sigismember de SIGUSR1");
            return -1;
        break;
        case 0:
            printf("Borrado");
            unlink(argv[0]);
        break;
    }

	return 0;
}