#include <linux/module.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Phan Cong Phong IU4-21M");
MODULE_DESCRIPTION("Module creates a folder and file in procfs and implements read and write callbacks");

/* global variable for sysfs folder hello */
static struct kobject *phong_kobj;

static char buffer_data[255];

static ssize_t phong_show(struct kobject *kobj, struct kobj_attribute *attr, char *buffer) {
	return snprintf(buffer, PAGE_SIZE, "%s", buffer_data);
}

static ssize_t phong_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buffer, size_t count) {
	strlcpy(buffer_data, buffer, sizeof(buffer_data));
	printk("You wrote '%s' to /sys/kernel/%s/%s\n", buffer, kobj->name, attr->attr.name);
	return count;
}

static struct kobj_attribute phong_attr = __ATTR(phong, 0660, phong_show, phong_store);


static int __init my_init(void){

	printk("sysfs_test - Creating /sys/kernel/hello/phong\n");
	phong_kobj = kobject_create_and_add("hello", kernel_kobj);
	if(!phong_kobj) {
		printk("Error creating /sys/kernel/hello\n");
		return -ENOMEM;
	}

	if(sysfs_create_file(phong_kobj, &phong_attr.attr)) {
		printk("Error creating /sys/kernel/hello/phong\n");
		kobject_put(phong_kobj);
		return -ENOMEM;
	}

    return 0;
}

static void __exit my_exit(void){
	printk("Deleting /sys/kernel/hello/phong\n");
	sysfs_remove_file(phong_kobj, &phong_attr.attr);
	kobject_put(phong_kobj);
}

module_init(my_init);
module_exit(my_exit);


// test

