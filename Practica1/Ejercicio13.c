#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char *argv[]){
    struct timeval tv;
    struct timezone tz;
    if(gettimeofday(&tv, &tz) == -1){
        printf("ERROR EN GETTIMEOFDAY 1 Nº: %d, %s \n", errno, strerror(errno));
        return -1;
    }
    suseconds_t ms1 = tv.tv_usec;
    int i;
    for(i = 0; i< 1000000; i++);
    if(gettimeofday(&tv, &tz)==-1){
        printf("ERROR EN GETTIMEOFDAY 2 Nº: %d, %s \n", errno, strerror(errno));
        return -1;
    }
    suseconds_t ms2 = tv.tv_usec;
    ms2 = ms2- ms1;
    printf("Tiempo que ha tardado un bucle en hacer 1000000 iteraciones(microsegundos): %ld\n", ms2);
    return 0;
}