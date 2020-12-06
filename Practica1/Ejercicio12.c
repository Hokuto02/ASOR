#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]){
    time_t  t = time(NULL);
    if(t == -1){
        printf("ERROR EN TIME Nº: %d, %s \n", errno, strerror(errno));
        return -1;
    }
    printf("La hora en segundos desde Epoch: %d\n", t);
    return 0;
}