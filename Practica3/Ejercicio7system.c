#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int ex;
    ex = system(argv[1]);
    if(ex == -1){
        perror("Error en system ");
        return -1;
    }
    printf("El comando termino de ejecutarse\n");
    return 0;
}