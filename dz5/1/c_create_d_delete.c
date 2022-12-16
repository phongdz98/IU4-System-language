#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#define C_OPTION "-c"
#define D_OPTION "-d"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s [OPTION] [DIRECTORY]\n", argv[0]);
        printf("Options:\n");
        printf("  -c    create a new directory\n");
        printf("  -d    delete a directory\n");
        return 1;
    }

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("Error code: %d\n", errno);
        printf("Error message: %s\n", strerror(errno));
        return 1;
    }

    strcat(cwd, "/");
    strcat(cwd, argv[2]);

    if (strcmp(argv[1], C_OPTION) == 0) {
        if (mkdir(cwd, 0777) == -1) {
            printf("Error code: %d\n", errno);
            printf("Error message: %s\n", strerror(errno));
        } else {
            printf("Create directory %s\n", cwd);
        }
    } else if (strcmp(argv[1], D_OPTION) == 0) {
        if (remove(cwd) == -1) {
            printf("Error code: %d\n", errno);
            printf("Error message: %s\n", strerror(errno));
        } else {
            printf("Delete directory %s\n", cwd);
        }
    }
    return 0;
}