#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int pd[2];
    pipe(pd);

    if (fork()) {
        char byte = 'x';
        write(pd[1], &byte, sizeof(byte));
        close(pd[1]);
        wait(0);
        read(pd[0], &byte, sizeof(byte));
        close(pd[0]);
        printf("%d: received pong\n", getpid());
    } else {
        char byte;
        read(pd[0], &byte, sizeof(byte));
        close(pd[0]);
        write(pd[1], &byte, sizeof(byte));
        close(pd[1]);
        printf("%d: received ping\n", getpid());
    }

    exit(0);
}