#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    long n;
    n = pathconf(".", _PC_LINK_MAX);
    if(n == -1)
        printf("ERROR EN PATHCONF _PC_LINK_MAX Nº: %d, %s \n", errno, strerror(errno));
    else 
        printf("The maximum  number of links to the file: %ld \n", n);
    n = pathconf(".", _PC_PATH_MAX);
    if(n == -1)
        printf("ERROR EN PATHCONF _PC_PATH_MAX Nº: %d, %s \n", errno, strerror(errno));
    else 
        printf("The maximum length of a relative pathname: %ld \n", n);
    n = pathconf(".", _PC_NAME_MAX);
    if(n == -1)
        printf("ERROR EN PATHCONF _PC_NAME_MAX Nº: %d, %s \n", errno, strerror(errno));
    else 
        printf("The maximum length of a filename in the directory: %ld \n", n);
    return 0;
}