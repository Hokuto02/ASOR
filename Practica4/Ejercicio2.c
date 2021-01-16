#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]){
    pid_t pid;
    int h_p[2];
    int p_h[2];
    int pi1 = pipe(h_p);
    int pi2 = pipe(p_h);
    if(pi1 == -1 || pi2 == -1){
        perror("Error pipie ");
        return-1;
    }
    pid = fork();
    switch(pid){
        case -1: //ERROR
            perror("Error fork ");
            return-1;
        case 0: //HIJO
            close(p_h[1]);
            close(h_p[0]);
            int cont = 0;
            char stdInP[256];
            char stdOutH;
            while(cont < 10){
                ssize_t size = read(p_h[0], &stdInP, 255);
                if(size == -1){
                    perror("Error read p_h ");
                    return-1;
                }
                stdInP[size] = '\n';
                if(write(1, &stdInP, size+1) == -1){
                    perror("Error write h_p l");
                    return-1;
                }
                cont++;
                sleep(1);
                if(cont == 10)
                    stdOutH = 'q';
                else
                    stdOutH = 'l';
                if(write(h_p[1], &stdOutH, 1) == -1){
                    perror("Error write h_p l");
                    return-1;
                }
            }
            _exit(0);
        break;
        default: //PADRE
            close(p_h[0]);
            close(h_p[1]);
            char stdInC[255];
            char stdInH[1];
            int ok = 0;
            while(1){
                ssize_t sizeR = read(0, &stdInC, 254);
                if(sizeR == -1){
                    perror("Error read stdIn ");
                    return-1;
                }
                stdInC[sizeR] = '\0';
                if(write(p_h[1], &stdInC, sizeR + 1) == -1){
                    perror("Error write p_h ");
                    return-1;
                }
                if(read(h_p[0], &stdInH, 1) == -1){
                    perror("Error read h_p");
                    return-1;
                }
                if(stdInH[0] == 'q')
                    break;
            }
            wait();
        break;
    }
    return 0;
}