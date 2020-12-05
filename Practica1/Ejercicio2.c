#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(setuid(0) == -1)
        printf("ERROR Nº: %d, %s \n", errno, strerror(errno));
    return 0;
}