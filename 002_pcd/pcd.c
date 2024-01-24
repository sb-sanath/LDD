#include <linux/module.h>
#include <linux/fs.h>			//for "alloc_chrdev_region"
#include <linux/kdev_t.h>		//for "dev_t"
#include <linux/printk.h>		//for pr_info
#include <linux/cdev.h>		//for Step 2

/* for Step 1 */
dev_t pcd_device_number;
const char pcd_name[] = "my_pcd_device";
#define NUMBER_OF_PCD_DEVICE	1

/* for Step 2 */
struct cdev pcd_cdev;
struct file_operations pcd_fops;

/* for Step 3 */
struct class *pcd_class;
struct device *pcd_device;

static int __init pcd_init(void){
	
	int ret;
	
	/* Step 1. Allocate device number for our pcd device */
	ret = alloc_chrdev_region(&pcd_device_number, 0, NUMBER_OF_PCD_DEVICE, pcd_name);
	if(ret < 0){
		pr_info("device number could not be allocated\n");
		goto out;
	}
	pr_info("minor no : %d \n major number : %d \n", MINOR(pcd_device_number), MAJOR(pcd_device_number));
	
	/* Step 2. char device registration with VFS */
	cdev_init(&pcd_cdev, &pcd_fops);
	//pcd_cdev.owner = THIS_MODULE;
	
	cdev_add(&pcd_cdev, pcd_device_number, NUMBER_OF_PCD_DEVICE);
	if(ret < 0){
		pr_err("Cdev add failed\n");
		goto unreg_chrdev;
	}
	
	/* Step 3. Dynamic device file creation */
	
	/* 3.1 : create device class under /sys/class/ */
	pcd_class = class_create(THIS_MODULE, pcd_name);
	if(IS_ERR(pcd_class)){
		pr_err("Class creation failed\n");
		ret = PTR_ERR(pcd_class);
		goto cdev_del;
	}
	
	/* 3.1 :  populate the sysfs with device information */
	pcd_device = device_create(pcd_class, NULL, pcd_device_number,  NULL, pcd_name);
	if(IS_ERR(pcd_device)){
		pr_err("Device create failed\n");
		ret = PTR_ERR(pcd_device);
		goto class_del;
	}
	
	return 0;
	
class_del:
	class_destroy(pcd_class);
cdev_del:
	cdev_del(&pcd_cdev);	
unreg_chrdev:
	unregister_chrdev_region(pcd_device_number,1);
out:
	pr_info("Module insertion failed\n");
	return ret;
}

static void __exit pcd_cleanup(void){
	device_destroy(pcd_class,pcd_device_number);
	class_destroy(pcd_class);
	cdev_del(&pcd_cdev);
	unregister_chrdev_region(pcd_device_number,1);
	pr_info("module unloaded\n");

}

module_init(pcd_init);
module_exit(pcd_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("JSR");
MODULE_DESCRIPTION("A simple hello world kernel module");
MODULE_INFO(board,"Beaglebone black REV A5");
