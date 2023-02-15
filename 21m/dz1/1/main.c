#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define READ 0
#define WRITE 1

int main(void){

    int p1[2], p2[2];
    pid_t pid;
    // Create pipes p1, p2
    if (pipe(p1) == -1){
        printf("Failed to create pipe p1.\n");
        return 1;
    }
    if (pipe(p2) == -1){
        printf("Failed to create pipe p2.\n");
        return 1;
    }
    // Create child process
    pid = fork();

    if(pid < 0){
        printf("Failed to create child process.\n");
        return 1;
    }

    if(pid > 0){
        // Parent process: write p1, read p2
        close(p1[READ]);
        close(p2[WRITE]);
        char *message1 = "Hello child process!";
        char buffer1[100];
        write(p1[WRITE],message1,strlen(message1)+1);
        read(p2[READ],buffer1,100);
        printf("Parent received:%s\n", buffer1);
        close(p1[WRITE]);
        close(p2[READ]); 

    }
    else {
        // Child process: write p2, read p1
        close(p1[WRITE]);
        close(p2[READ]);
        char *message2 = "Hello parent process!";
        char buffer2[100];
        write(p2[WRITE],message2,strlen(message2)+1);
        read(p1[READ],buffer2,100);
        printf("Child received:%s\n", buffer2);
        close(p2[WRITE]);
        close(p1[READ]); 
    }

    return 0;
}