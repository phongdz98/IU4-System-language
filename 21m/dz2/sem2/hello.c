#include <linux/module.h>
#include <linux/init.h>

// Meta Information

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Phan Cong Phong");
MODULE_DESCRIPTION("A hello world kernel module");

static  int __init init_hello(void){
    printk("Hello Kernel!\n");
    return 0;
}

static void __exit exit_hello(void){
    printk("Goodbye, Kernel!\n");
}

module_init(init_hello);
module_exit(exit_hello);