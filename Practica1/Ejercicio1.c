#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(setuid(0) == -1)
        perror("ERROR");
    return 0;
}

