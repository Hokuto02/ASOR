#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
    int fd;
    fd = open(argv[1], O_TRUNC | O_WRONLY);
    if(fd == -1){
        perror("Error open ");
        return-1;
    }
    char l[255];
    strcpy(l, argv[2]);
    strcat(l, "\n");
    if(write(fd, l, strlen(l)) == -1){
        perror("Error open ");
        return-1;
    }
    return 0;
}