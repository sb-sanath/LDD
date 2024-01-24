#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

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
	{ 0x28e00715, "module_layout" },
	{ 0x3a06a966, "device_destroy" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x17075bc7, "cdev_del" },
	{ 0xa0f33f8, "class_destroy" },
	{ 0x1085cb67, "device_create" },
	{ 0x62520095, "__class_create" },
	{ 0x585c6131, "cdev_add" },
	{ 0x451a6882, "cdev_init" },
	{ 0xc5850110, "printk" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "712E7577B680CE54814D0A3");
