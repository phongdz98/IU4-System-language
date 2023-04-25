#include "chrdev/dz_chrdev.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int ioctl_set_msg_hexnum;
int ioctl_get_msg_hexnum;

char* read_line(FILE *fin){
	char *buffer;
	char *tmp;
	int read_chars = 0;
	int bufsize = 128;
	char *line = malloc(bufsize);
	if (!line){
		return NULL;
	}
	buffer = line;
	while (fgets(buffer, bufsize - read_chars, fin)){
		read_chars = strlen(line);
		if (line[read_chars - 1] == '\n'){
			line[read_chars - 1] = '\0';
			return line;
		} else{
			bufsize = 2 * bufsize;
			tmp = realloc(line, bufsize);
			if (tmp){
				line = tmp;
				buffer = line + read_chars;
			} else{
				free(line);
				return NULL;
			}
		}
	}
	return NULL;
}

int ioctl_get_major_by_dev_name(char* dev_name, int* dev_major_ptr){

	char* target_file = "/proc/devices";
	char* file_mode = "r";
	char* entry;
	char* line;
	char* line_tmp = (char*)malloc(128*sizeof(char));
	int diff;
	int major_num_size = 0;
	int i;
	FILE* fin;

	printf("Start search major of device %s in %s...\n\r", dev_name, target_file);

	fin = fopen(target_file, file_mode);
	if (fin){
		while (line = read_line(fin)){
			if ( entry = strstr(line, dev_name) ){
				diff = entry - line;
				major_num_size = diff - 1;
				i = 0;
				while (line[diff+i] == dev_name[i]){
					if ((line[diff+i] == '\0') && (dev_name[i] == '\0')){
						strncpy(line_tmp, line, major_num_size);
						*dev_major_ptr = atoi(line_tmp);
					}
					i++;
				}
			}
			free(line);
		}
		free(line_tmp);
	} else{
		printf("Unable to open /proc/devices...\n\r");
		exit(-1);
	}
	fclose(fin);

	if (*dev_major_ptr == 0){
		printf("MAJOR OF DEVICE %s NOT FOUND(%d)\n\rITS WRONG, PLEASE INSERT MODULE\n\r", dev_name, *dev_major_ptr);
		exit(-1);
	} else{
		printf("Major of device %s found: %d\n\n\r", dev_name, *dev_major_ptr);
	}
	return 0;
}

int ioctl_set_msg(int loc_fd, char *loc_msg_ptr){

	int err_retn = 0;
	err_retn = ioctl(loc_fd, ioctl_set_msg_hexnum, loc_msg_ptr);

	if (err_retn < 0){
		printf("ioctl_set_msg err: %d\n\r", err_retn);
		exit(-1);
	}
}

int ioctl_get_msg(int loc_fd){

	int err_retn;
	char msg[IOCTL_MAX_SIZE];

	err_retn = ioctl(loc_fd, ioctl_get_msg_hexnum, msg);

	if (err_retn < 0) {
		printf("ioctl_get_msg err: %d\n\r", err_retn);
		exit(-1);
	}
	printf("%s\n\r", msg);
}

int menu_input(int* loc_cur_ptr){

	printf("Please enter:\n\r1 -> ioctl write\n\r2 ->  ioctl read\n\r3 -> exit\n\r");
	scanf("%31d", loc_cur_ptr);
	return 0;
}

int main(){

        int fd_device = 0;
        int in_menu = 1;
	int* dev_major_ptr = (int*)malloc(sizeof(int));
	int* cur_ptr = (int*)malloc(sizeof(int));
	char* msg_ptr = (char*)malloc(IOCTL_MAX_SIZE*sizeof(char));

	*dev_major_ptr = 0;
	ioctl_get_major_by_dev_name(DEVICE_NAME, dev_major_ptr);

	ioctl_set_msg_hexnum = _IOW(*dev_major_ptr, 0, char*);
	ioctl_get_msg_hexnum = _IOR(*dev_major_ptr, 1, char*);

	fd_device = open(DEVICE_FILE_NAME, 0);
	if (fd_device < 0){
		printf("Unable to open device file %s\n\r", DEVICE_FILE_NAME);
		exit(-1);
	}

	while(in_menu) {
		menu_input(cur_ptr);
		switch (*cur_ptr) {
			case 1:
				printf("Enter msg:\n\r-> ");
				scanf(" %127[^\n]s", msg_ptr);
				ioctl_set_msg(fd_device, msg_ptr);
				break;
			case 2:
				printf("Ur msg: --> ");
				ioctl_get_msg(fd_device);
				break;
			case 3:
				in_menu = 0;
				break;
			case 69:
				printf("LOL BECH U REALLY WANNA C SAM KEKES CODES???????\n\r");
				printf("ENTA CKRET 4 SAM KEKEKODES EUUUU:\n\r-> ");
				scanf(" %127[^\n]s", msg_ptr);
				if (strcmp(msg_ptr,"DEADBEEF") == 0){
					printf("C UR KEKES BECH:\n\rIOCTL_SET_MSG: --> 0x%x\n\rIOCTL_GET_MSG: --> 0x%x\n\r", ioctl_set_msg_hexnum, ioctl_get_msg_hexnum);
				} else {
					printf("BBBAADDD CKRET BECH EUUUU: %s!!!!!!\n\r", msg_ptr);
				}
				break;
			default:
				printf("Wrong enter, u in default branch...\n\r");
				break;
		}
	}
	close(fd_device);
}