#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
    int i;
    for(i = 0; i <= 255; i++){
        printf("ERROR Nº: %d, %s \n", i, strerror(i));
    } 
    return 0;
}