#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char *argv[]){
    time_t  t = time(NULL);
    if(t == -1){
        printf("ERROR EN TIME Nº: %d, %s \n", errno, strerror(errno));
        return -1;
    }
    struct tm *hora = localtime(&t);
    if(hora == NULL){
       printf("ERROR EN LOCALTIME Nº: %d, %s \n", errno, strerror(errno));
        return -1; 
    }
    printf("Year : %i\n", hora->tm_year + 1900);
    return 0;
}