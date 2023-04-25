#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include "char_dev.h"

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Phan Cong Phong IU4-21M");
MODULE_DESCRIPTION("Linux Character Device with IOCTL");


// Buffer for data
static char buffer[255];
static int buffer_pointer = 0;

// variables for device and device class
static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

#define DRIVER_NAME "mychardev"
#define DRIVER_CLASS "MyModuleClass"

static int driver_open(struct inode *device_file, struct file *instance);
static int driver_close(struct inode *device_file, struct file *instance) ;
static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) ;
static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs);
static long int my_ioctl(struct file *file, unsigned cmd, unsigned long arg);

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,   
	.release = driver_close,  
	// .read = driver_read,   
	// .write = driver_write,
    .unlocked_ioctl = my_ioctl
};


static int __init ModuleInit(void){
    int err = 0;
    int major , minor;
    printk("Hello Kernel!\n");
    // Allocate a device nr
    err = alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME);
    if (err < 0) {
        printk(KERN_ALERT "Failed to allocate device number\n");
        return err;
    }
    major = MAJOR(my_device_nr);
    minor = MINOR(my_device_nr);
    printk(KERN_INFO "Major number: %d, Minor number: %d\n", major, minor);

    // Create device class
    my_class = class_create(THIS_MODULE, DRIVER_CLASS);
    if(IS_ERR(my_class)){
        printk(KERN_ALERT "Failed to create class\n");
        unregister_chrdev_region(my_device_nr, 1);
        return PTR_ERR(my_class);
    }

    // Create device file
    if(device_create(my_class, NULL, my_device_nr,NULL, DRIVER_NAME )==NULL){
        printk(KERN_ALERT "Can not create device file!");
        class_destroy(my_class);
        return -1;
    }

    // Initialize device file
    cdev_init(&my_device,&fops);
    err = cdev_add(&my_device, my_device_nr, 1);
    if(err < 0){
        printk(KERN_ALERT"Failed to add cdev\n");
        device_destroy(my_class, my_device_nr);
        return err;

    }
    return 0;


}

static void __exit ModuleExit(void){
    cdev_del(&my_device);
    device_destroy(my_class,my_device_nr);
    class_destroy(my_class);
    unregister_chrdev_region(my_device_nr, 1);
    printk("Goodbye Kernel!\n");

}


module_init(ModuleInit);
module_exit(ModuleExit);

static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) {
	int to_copy, not_copied, delta;

	// Get amount of data to copy 
	to_copy = min((int)count, (int)buffer_pointer);

	// Copy data to user
	not_copied = copy_to_user(user_buffer, buffer, to_copy);

	// Calculate data 
	delta = to_copy - not_copied;

	return delta;
}

//Write data to buffer

static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs) {
	int to_copy, not_copied, delta;

	// Get amount of data to copy 
	to_copy = min((int)count, (int)sizeof(buffer));

	// Copy data to user
	not_copied = copy_from_user(buffer, user_buffer, to_copy);
	buffer_pointer = to_copy;

	// Calculate data 
	delta = to_copy - not_copied;

	return delta;
}

//This function is called, when the device file is opened
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("mychardev - open was called!\n");
	return 0;
}

//This function is called, when the device file is opened
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("mychardev - close was called!\n");
	return 0;
}


// ioctl function
static long int my_ioctl(struct file *file, unsigned cmd, unsigned long arg){
    int res = 0;
    int *argp = (int *)arg;

	switch(cmd){
		case WR_VALUE:
            driver_write(file, (char *)arg, BUFFER_SIZE, 0);
			break;
		case RD_VALUE:
            driver_read(file, (char *)arg, BUFFER_SIZE, 0);
			break;
        case GET_MAJOR:
            res = imajor(file->f_inode);
            if (copy_to_user(argp, &res, sizeof(res))) {
                return -EFAULT;
            }
            break;
        case CLEAR_DATA:
            memset(buffer, 0, sizeof(buffer));
            break;

	}
	return 0;
}