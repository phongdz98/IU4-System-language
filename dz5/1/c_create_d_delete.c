#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct stat st = {0};

int main(int argc, char *argv[]){
    if(strcmp(argv[1],"-c")==0){
        if ((stat(argv[2], &st) == -1)) {
        mkdir(argv[2], 0777);
        printf("Create directory %s\n",argv[2]);
        }
    }
    else if (strcmp(argv[1],"-d")==0){
        if ((stat(argv[2], &st) != -1)){
            rmdir(argv[2]);
            printf("Delete directory %s\n",argv[2]);
        }

    }

    return 0;
}