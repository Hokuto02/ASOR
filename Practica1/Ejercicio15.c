#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <locale.h>

int main(int argc, char *argv[]){
    if(setlocale(LC_ALL, "es_ES") == NULL){
        printf("ERROR EN SETLOCALE Nº: %d, %s \n", errno, strerror(errno));
        return -1;
    }
    time_t  t = time(NULL);
    if(t == -1){
        printf("ERROR EN TIME Nº: %d, %s \n", errno, strerror(errno));
        return -1;
    }
    struct tm *hora = localtime(&t);
    if(hora == NULL){
        printf("ERROR EN LOCALTIME Nº: %d, %s \n", errno, strerror(errno));
        return -1; 
    }
    char s[255];
    if (strftime(s, 255, "%A, %d de %B de %Y, %R", hora) == 0){
        printf("ERROR EN STRFTIME Nº: %d, %s \n", errno, strerror(errno));
        return -1; 
    }
    printf("%s\n", s);
    return 0;
}