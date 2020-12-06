#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    uid_t uid = getuid();
    uid_t euid = geteuid();
    printf("ID real del usuario: %d\n", uid);
    printf("ID efectivo del usuario: %d\n", euid);
    printf("Cuando el fichero del programa tiene el bit setuid activado el EUID del proceso creado se cambia al usuario del fichero\n", uid);
    return 0;
}