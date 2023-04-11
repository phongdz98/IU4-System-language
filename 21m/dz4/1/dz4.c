#include<linux/module.h>
#include<linux/init.h>
#include<linux/proc_fs.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Phan Cong Phong IU4-21M");
MODULE_DESCRIPTION("Module creates a folder and file in procfs and implements read and write callbacks");


static struct proc_dir_entry *proc_folder;
static struct proc_dir_entry *proc_file;

//moi them vao
static char buffer[255];
static int buffer_pointer = 0;


static ssize_t my_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) {
	// char text[] = "Hello from a procfs file!\n";
	int to_copy, not_copied, delta;

	/* Get amount of data to copy */
	to_copy = min((int)count, (int)buffer_pointer);

	/* Copy data to user */
	not_copied = copy_to_user(user_buffer, buffer, to_copy);

	/* Calculate data */
	delta = to_copy - not_copied;

	return delta;
}


static ssize_t my_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs) {
	int to_copy, not_copied, delta;

	/* Get amount of data to copy */
	to_copy = min((int)count, (int)sizeof(buffer));

	/* Copy data to user */
	not_copied = copy_from_user(buffer, user_buffer, to_copy);
	buffer_pointer = to_copy;
	printk("dz4 - You have written %s to me\n", buffer);
	/* Calculate data */
	delta = to_copy - not_copied;

	return delta;
}


static struct proc_ops fops = {
	.proc_read = my_read,
	.proc_write = my_write,
};


static int __init my_init(void){
    /* /proc/hello/phong */
    proc_folder = proc_mkdir("hello", NULL);
    if(proc_folder == NULL){
        printk("dz4 - Error creating /proc/hello\n");
        return -ENOMEM;
    }

    proc_file = proc_create("phong", 0666, proc_folder, &fops);
        if(proc_file == NULL){
        printk("dz4 - Error creating /proc/hello/phong\n");
        proc_remove(proc_folder);
        return -ENOMEM;
    }

    printk("dz4 - Created /proc/hello/phong\n");

    return 0;
}

static void __exit my_exit(void){
    printk("dz4 - Removing /proc/hello/phong\n");
    proc_remove(proc_file);
    proc_remove(proc_folder);

}

module_init(my_init);
module_exit(my_exit);

