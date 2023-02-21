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
    int sockfd = -1; //socket
    struct sockaddr_in server_addr; //adress server
    char recv_buffer[1024]; // buffer for receive
    time_t ticks;

    memset(recv_buffer, 0, sizeof(recv_buffer));
    memset(&server_addr, 0, sizeof(server_addr));

    sockfd = socket(AF_INET, SOCK_STREAM, 0 );//IPv4, TCP, default protocol
                                              //create socket for connecting
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//adress server 
                                                         //127.0.0.1  : loopback adress
    server_addr.sin_port = htons(5000); // port server

    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))==0){
        read(sockfd, recv_buffer, sizeof(recv_buffer)-1);
        printf("\n%s\n", recv_buffer);
        
    }
    close(sockfd);
}
