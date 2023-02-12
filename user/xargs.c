#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAXLEN 128

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("xargs: arguments error");
        exit(1);
    }

    char *inputs[MAXARG + 1];
    int i = 0;
    for (int j = 1; j < argc; j++) {
        inputs[i++] = argv[j];
    }
    for (; i <= MAXARG; i++) {
        inputs[i] = (char *) malloc(sizeof(MAXLEN + 1));
    }

    char buf;
    int read_flag;
    while (1) {
        i = argc - 1;
        int k = 0;
        while ((read_flag = read(0, &buf, 1)) > 0) {
            if (i == MAXARG) {
                break;
            }
            if (k == MAXLEN) {
                inputs[i++][k] = 0;
                break;
            }

            if (buf == '\n') {
                inputs[i++][k] = 0;
                break;
            } else {
                inputs[i][k++] = buf;
            }
        }

        inputs[i] = 0;
        int pid;
        if ((pid = fork()) == 0) {
            exec(inputs[0], inputs);
        } else {
            wait(0);
        }

        if (read_flag <= 0) {
            break;
        }
    }
    exit(0);
}