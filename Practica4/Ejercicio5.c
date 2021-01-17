#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    int fdPipe1 = open(argv[1], O_NONBLOCK | O_RDONLY) ;
    int fdPipe2 = open(argv[2], O_NONBLOCK | O_RDONLY);
    if(fdPipe2 == -1 || fdPipe1 == -1){
        perror("Error open ");
        return -1;
    }
    fd_set readfds;
    int fdact;
    int numpi;
    ssize_t size = 256;
    char bufPipe[size];
    do{
        FD_ZERO(&readfds); 
        FD_SET(fdPipe1, &readfds); 
        FD_SET(fdPipe2, &readfds);  
        if(select((fdPipe1 < fdPipe2)? fdPipe2 + 1:fdPipe1 + 1 , &readfds, NULL, NULL, NULL) == -1){
            perror("Error select ");
            return -1;
        }

        if(FD_ISSET(fdPipe1, &readfds)){
            fdact = fdPipe1;
            numpi = 1;
        }else if(FD_ISSET(fdPipe2, &readfds)){
            fdact = fdPipe2;
            numpi = 2;
        }

        size = read(fdact, bufPipe, 255);
        if(size == -1){
            perror("Error read ");
            return -1;
        }
        bufPipe[size] = '\0';
        printf("Pipe %i, dice: %s\n", numpi, bufPipe);

        if(fdact == fdPipe1){
            close(fdPipe1);
            fdPipe1 = open(argv[1], O_NONBLOCK | O_RDONLY);
            if(fdPipe1 == -1){
                perror("Error open 1 de nuevo ");
                return -1;
            }
        }else if(fdact == fdPipe2){
            close(fdPipe2);
            fdPipe2 = open(argv[2], O_NONBLOCK | O_RDONLY);
            if(fdPipe2 == -1){
                perror("Error open 2 de nuevo ");
                return -1;
            }
        }
    }while(1);
    close(fdPipe1);
    close(fdPipe2);
    return 0;
}