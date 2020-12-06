#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

int main(int argc, char *argv[]){
    uid_t uid = getuid();
    uid_t euid = geteuid();
    printf("ID real del usuario: %d\n", uid);
    printf("ID efectivo del usuario: %d\n", euid);
    struct passwd *p = getpwuid(uid);
    if(p == NULL){
        printf("ERROR EN GETPWUID Nº: %d, %s \n", errno, strerror(errno));
        return -1;
    }
    printf("Username: %s\n", p->pw_name);
    printf("Home directory: %s\n", p->pw_dir);
    printf("User information: %s\n", p->pw_gecos);
    return 0;
}