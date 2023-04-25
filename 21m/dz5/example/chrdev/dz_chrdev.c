#include <linux/init.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/poll.h>
#include <linux/cdev.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>

#include "dz_chrdev.h"

MODULE_AUTHOR("Chpeckdev");
MODULE_LICENSE("GPL");

int init_module(void);
void cleanup_module(void);

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);

static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
long chpeck_ioctl_chrdev(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param);

static int dev_major;
static struct class* class_chpeckdev;
static int Device_Open = 0;

static char msg[CHRDEV_BUF_LEN_MSG];
static char *msg_Ptr;

static struct file_operations fo = {
  .read = device_read,
  .write = device_write,
  .unlocked_ioctl = chpeck_ioctl_chrdev,
  .open = device_open,
  .release = device_release
};

int init_module(void){

	dev_major = register_chrdev(0, DEVICE_NAME, &fo);
	if (dev_major < 0){
		printk("Dev failed %d\n\r", dev_major);
		return dev_major;
  	}
	class_chpeckdev = (struct class*)class_create(THIS_MODULE, DEVICE_NAME);
	device_create(class_chpeckdev, NULL, MKDEV(dev_major, 0), NULL, DEVICE_NAME);
	return 0;
}

void cleanup_module(void){

	device_destroy(class_chpeckdev, MKDEV(dev_major, 0));
	class_destroy(class_chpeckdev);
	unregister_chrdev(dev_major, DEVICE_NAME);
}

static int device_open(struct inode *inode, struct file *file){

	if (Device_Open){
		return -EBUSY;
	}
	Device_Open++;
	msg_Ptr = msg;
	try_module_get(THIS_MODULE);
	return 0;
}

static int device_release(struct inode *inode, struct file *file){

	Device_Open--;
	module_put(THIS_MODULE);
	return 0;
}

static ssize_t device_read(struct file *filp, char *buff,  size_t len, loff_t * offset){

	int bytes_read = 0;

	if (*msg_Ptr == 0){
		return 0;
	}
	while (len && *msg_Ptr){
		put_user(*(msg_Ptr++), buff++);
		len--;
		bytes_read++;
	}
	return bytes_read;
}

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off){

	int i = 0;

	if (len > CHRDEV_BUF_LEN_MSG){
		return -EINVAL;
	}
	memset(msg, 0, CHRDEV_BUF_LEN_MSG);
	msg_Ptr = msg;
	for (i = 0; i < len && i < CHRDEV_BUF_LEN_MSG; i++){
		get_user(msg[i], buff + i);
	}
	return i;
}

long chpeck_ioctl_chrdev(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param){
	int ioctl_set_msg_hexnum = _IOW(dev_major, 0, char*);
	int ioctl_get_msg_hexnum = _IOR(dev_major, 1, char*);
	int i = 0;
	char* tmp;
	char ch;
	if (ioctl_num == ioctl_set_msg_hexnum){
		tmp = (char *)ioctl_param;
		get_user(ch, tmp);
		for (i = 0; ch && i < CHRDEV_BUF_LEN_MSG; i++, tmp++){
			get_user(ch, tmp);
		}
		device_write(file, (char*)ioctl_param, i, 0);
	} else if (ioctl_num == ioctl_get_msg_hexnum){
		i = device_read(file, (char*)ioctl_param, CHRDEV_BUF_LEN_MSG, 0);
		put_user('\0', (char*)ioctl_param + i);
	} else{
		tmp = "HEU BABE ITS WRONG ioctl_num CHECK IT";
		device_write(file, tmp, 37, 0);
		i = device_read(file, (char*)ioctl_param, CHRDEV_BUF_LEN_MSG, 0);
		put_user('\0', (char*)ioctl_param + i);
	}
	return 0;
}