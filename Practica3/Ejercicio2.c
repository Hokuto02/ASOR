#include <sched.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    int  politica;
    politica = sched_getscheduler(getpid());
    if(politica == -1){
        perror("Error sched_getscheduler ");
        return -1;
    }
    printf("Politica :");
    switch(politica){
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
        break;
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
        break;
        case SCHED_RR:
            printf("SCHED_RR\n");
        break;
        default:
            printf("No concide con una politica.\n");
        break;
    }
    int parametros;
    struct sched_param param;
    parametros = sched_getparam(getpid(), &param);
    if(parametros == -1){
        perror("Error sched_getparam ");
        return -1;
    }
    printf("La prioridad del proceso actual es: %i\n", param.sched_priority);

    int max;
    max = sched_get_priority_max(politica);
    if(max == -1){
        perror("Error sched_get_priority_max ");
        return -1;
    }
    printf("Valor maximo de la prioridad: %i\n", max);
    int min;
    min = sched_get_priority_min(politica);
    if(min == -1){
        perror("Error sched_get_priority_min ");
        return -1;
    }
    printf("Valor minimo de la prioridad: %i\n", min);
    return 0;
}