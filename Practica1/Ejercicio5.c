#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>

int main(int argc, char *argv[]){
    struct utsname buf;
    if(uname(&buf) == -1){
        printf("ERROR EN UNAME Nº: %d, %s \n", errno, strerror(errno));
        return -1;
    } 
    printf("System name: %s \n", buf.sysname);
    printf("Node name: %s \n", buf.nodename);
    printf("Operating system release: %s \n", buf.release);
    printf("Operating system version: %s \n", buf.version);
    printf("Hardware identifier: %s \n", buf.machine);
    return 0;
}