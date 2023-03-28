#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 255
int main(){
    int fd;
    char buffer[BUFFER_SIZE];
    char data[BUFFER_SIZE];
    // open device file
    fd = open("/dev/mychardev", O_RDWR);
    if (fd < 0) {
        printf("Failed to open device file.\n");
        return -1;
    }
    // Read data from user
    printf("Enter data to write to device: ");
    fgets(data, BUFFER_SIZE, stdin);
    // Write data to device
    printf("Writing data to device...\n");
    write(fd, data, strlen(data));
    // Read data from device
    printf("Reading data from device...\n");
    read(fd, buffer, BUFFER_SIZE );
    printf("Data read from device:%s\n", buffer);
    // close device
    close(fd);
    return 0;
}