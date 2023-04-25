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
	{ 0x14622be2, "module_put" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x1b978574, "try_module_get" },
	{ 0x167e7f9d, "__get_user_1" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0xc3aaf0a9, "__put_user_1" },
	{ 0xd518750b, "__register_chrdev" },
	{ 0xbc9e3bc0, "__class_create" },
	{ 0xc6b45c91, "device_create" },
	{ 0x92997ed8, "_printk" },
	{ 0x4d6e8735, "device_destroy" },
	{ 0x4b359343, "class_destroy" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x1b71f472, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "3AB8F0EC923131B6AE50366");
