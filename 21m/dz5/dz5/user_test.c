#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>
#include "char_dev/char_dev.h"

#define BUFFER_SIZE 255


int main(){
    int in_menu = 1;
    int fd,answer;
    int major_num = 0;
    char buffer[BUFFER_SIZE];
    char data[BUFFER_SIZE];
    // open device file
    fd = open("/dev/mychardev", O_RDWR);
    if (fd < 0) {
        printf("Failed to open device file.\n");
        return -1;
    }
    while (in_menu)
    {
        printf("Please enter:\n\r1:ioctl write\n\r2:ioclt read\n\r3: major and ioctl number info\n\r4:ioctl clear data\n\r5:exit\n\r");
        scanf("%d", &answer);
        switch (answer)
        {
        case 1:
            printf("Enter data to write to device: ");
            getchar();
            fgets(data, BUFFER_SIZE, stdin);
            printf("Writing data to device...\n");
            if(ioctl(fd, WR_VALUE, data) < 0) {
                perror("ioctl");
                return errno;
            }
            break;
        case 2:
            printf("Reading data from device...\n");
            if(ioctl(fd, RD_VALUE, buffer) < 0) {
                perror("ioctl");
                return errno;
            }
            printf("Data read from device:%s\n", buffer);
            break;
        case 3:
            printf("Reading info.....\n");
            if (ioctl(fd, GET_MAJOR, &major_num) < 0) {
                perror("ioctl failed");
                return -1;
            }
            printf("Major number: %d\n", major_num);
            printf("icotl numbers: read - 0x%lx, write - 0x%lx\n",RD_VALUE ,WR_VALUE);
            break;
        case 4:
            printf("Clear data.....\n");
            if (ioctl(fd, CLEAR_DATA) < 0) {
                perror("ioctl failed");
                return -1;
            }
            printf("Done!!!");
            break;
            
        case 5:
            in_menu=0;
            break;

        default:
            printf("Number need <= 6");
            break;
        }

    }

    close(fd);
    return 0;
}
