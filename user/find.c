#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

void dfs(int fd, char *dirname, char *filename) {
    char buf[512], *p;
    struct dirent de;
    struct stat st;

    strcpy(buf, dirname);
    p = buf + strlen(dirname);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
        if (de.inum == 0)
            continue;
        
        if  (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) {
            continue;
        }
        
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if (strcmp(de.name, filename) == 0) {
            printf("%s\n", buf);
        }

        if (stat(buf, &st) < 0) {
            continue;
        }

        if (st.type == T_DIR)
        {
            int child_fd = open(buf, 0);
            if (child_fd < 0)
            {
                fprintf(2, "find: cannot open %s\n", buf);
                continue;
            }
            dfs(child_fd, buf, filename);
            close(child_fd);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        exit(1);
    }
    
    char* dir = argv[1];
    int fd;
    struct stat st;
    if ((fd = open(dir, 0)) < 0)
    {
        fprintf(2, "find: cannot open %s\n", dir);
        exit(1);
    }
    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", dir);
        close(fd);
        exit(1);
    }
    if (st.type != T_DIR) {
        fprintf(2, "find: first parameter should be a directory\n");
        close(fd);
        exit(1);
    }

    dfs(fd, dir, argv[2]);
    close(fd);
    exit(0);
}
