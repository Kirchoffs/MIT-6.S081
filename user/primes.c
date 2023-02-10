#include "kernel/types.h"
#include "user/user.h"

void redirect(int k, int pd[2]) {
    close(k);
    dup(pd[k]);
    close(pd[0]);
    close(pd[1]);
}

void source() {
    int n;
    for (n = 2; n <= 35; n++) {
        write(1, &n, 4);
    }
}

void cull(int p) {
    int n;
    for (;;) {
        if (read(0, &n, 4) == 0) {
            exit(0);
        }
        if (n % p != 0) {
            write(1, &n, 4);
        }
    }
}

void sink() {
    int pd[2];
    int p;
    for (;;) {
        if (read(0, &p, 4) == 0) {
            exit(0);
        }
        printf("prime %d\n", p);
        pipe(pd);
        if (fork()) {
            redirect(0, pd);
            continue;
        } else {
            redirect(1, pd);
            cull(p);
        }
    }
}

int main(int argc, char *argv[]) {
    int pd[2];
    pipe(pd);

    if (fork()) {
        redirect(0, pd);
        sink();
    } else {
        redirect(1, pd);
        source();
    }

    exit(0);
}
