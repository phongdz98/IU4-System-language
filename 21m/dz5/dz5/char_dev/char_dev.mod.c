#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x92997ed8, "_printk" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x7682ba4e, "__copy_overflow" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xbc9e3bc0, "__class_create" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xc6b45c91, "device_create" },
	{ 0x4b359343, "class_destroy" },
	{ 0xe56276c3, "cdev_init" },
	{ 0x1cf5d0cd, "cdev_add" },
	{ 0x4d6e8735, "device_destroy" },
	{ 0xecd97942, "cdev_del" },
	{ 0x1b71f472, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "1B541F9765B86E974F33A9C");
