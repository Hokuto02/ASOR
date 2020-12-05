#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    long n;
    n = sysconf(_SC_ARG_MAX);
    if(n == -1)
        printf("ERROR EN SYSCONF _SC_ARG_MAX Nº: %d, %s \n", errno, strerror(errno));
    else 
        printf("The maximum length of the arguments: %ld \n", n);
    n = sysconf(_SC_CHILD_MAX);
    if(n == -1)
        printf("ERROR EN SYSCONF _SC_CHILD_MAX Nº: %d, %s \n", errno, strerror(errno));
    else 
        printf("The maximum number of simultaneous processes per user ID: %ld \n", n);
    n = sysconf(_SC_OPEN_MAX);
    if(n == -1)
        printf("ERROR EN SYSCONF _SC_OPEN_MAX Nº: %d, %s \n", errno, strerror(errno));
    else 
        printf("The maximum number of files that a process can have open at any time: %ld \n", n);
    return 0;
}