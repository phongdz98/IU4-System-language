#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<time.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<unistd.h>

void main(){
    int listenfd = -1; // listen 
    int connfd = -1;   // connect
    struct sockaddr_in server_addr;
    char recv_buffer[1024]; // buffer for receive
    char send_buffer[1024]; // buffer for sending data
    time_t ticks;

    memset(recv_buffer, 0, sizeof(recv_buffer));
    memset(send_buffer, 0, sizeof(send_buffer));
    memset(&server_addr, 0, sizeof(server_addr));

    listenfd = socket(AF_INET, SOCK_STREAM, 0); // create socket for listening
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr)); //bind socket to server adress
    listen(listenfd, 10);// listen for incoming connections , max 10

    while(1){
        connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);
        // struct sockaddr_in client_addr;
        // int client_len = sizeof(client_addr);
        // getpeername(connfd, (struct sockaddr*)&client_addr, &client_len);
        // printf("Client connected with IP address: %s\n", inet_ntoa(client_addr.sin_addr));
        ticks = time(NULL);
        read(connfd, recv_buffer, sizeof(recv_buffer)-1);
        printf("\nReceived messeage from client:%s\n", recv_buffer);
        sprintf(send_buffer, "Server reply %s", ctime(&ticks));
        write(connfd, send_buffer, strlen(send_buffer));
        close(connfd);

    }
    close(listenfd);

}