/*Character Device Driver*/



/* For loading and initialising any module*/
#include <linux/init.h>
#include <linux/module.h>

/*character driver support*/
#include <linux/fs.h>

/*Using important predefined structures for character devices*/
#include <linux/cdev.h>

/*For exchanging data with user*/
#include <linux/uaccess.h>

/*For blocking I/O */
#include <linux/wait.h>



/*macros*/
#define DEVICE_NAME "character_device"
#define SPACE 256
#define SUCCESS 0


/*Declaring the License associated*/
MODULE_LICENSE("Dual BSD/GPL");



/*Declaring variables*/
static struct cdev my_cdev;
static dev_t dev;
static unsigned int firstminor = 0, count = 1, bytes = -1, error = 0;	
static char memory[SPACE], * memory_ptr;
	/*
	 * count is the total number of contiguous device numbers requested.
	 * firstminor is the requested minor number of the char device.
	 * usually firstminor is zero!
	 * */



/*Defining functions
 * NOTE: write must not return 0 or else we get an endless call for write
 * NOTE: KERN_ALERT is causing some glitches.
 */
static int real_open(struct inode *pinode, struct file *pfile)
{
	printk(KERN_INFO "%s", __FUNCTION__);
	
	memory_ptr = memory;
	
	return SUCCESS;
}
static int real_close(struct inode *pinode, struct file *pfile)
{
	printk(KERN_INFO "%s\n\n", __FUNCTION__);
	
	memory_ptr = 0;
	
	return SUCCESS;
}


ssize_t real_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
	printk(KERN_INFO "%s", __FUNCTION__);
	if(length>0)
	{			
		for(bytes=0;bytes<length;bytes++)
		{
			error = put_user(*memory_ptr, buffer);
			if(error==0)
			{
				memory_ptr++;
				buffer++;
			}
			else
			{
				bytes = -EFAULT;
				printk(KERN_INFO "Error occured while reading ... ");
				break;
			}
		}
	}
	return bytes;
}
ssize_t real_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
	printk(KERN_INFO "%s", __FUNCTION__);
	if(length>0)
	{			
		for(bytes=length;bytes<SPACE;bytes++)
		{
			memory[bytes]=0;
		}
		for(bytes=0;bytes<length;bytes++)
		{
			error = get_user(*memory_ptr, buffer);
			if(error==0 && bytes<SPACE)
			{
				memory_ptr++;
				buffer++;
			}
			else
			{
				printk(KERN_INFO "Error occured while writing ... ");
				bytes = -EFAULT;
				break;
			}
		}
	}
	return bytes;	/*NOTE: Here bytes must be NON-ZERO */	
}


/*Connecting defined functions with standard file operations defined as file_operations in linux/fs.h*/
struct file_operations perform_me = {
	.owner   = THIS_MODULE,
	.open    = real_open,
	.read    = real_read,
	.write   = real_write,
	.release = real_close,	
};


static int starting_function(void)
{
	alloc_chrdev_region(&dev, firstminor, count, DEVICE_NAME);
	
	cdev_init(&my_cdev, &perform_me);
	cdev_add(&my_cdev, dev, count);
	
	sprintf(memory, "You can read & write now! with a limit of %d characters :P", SPACE);
	
	printk(KERN_INFO "CHARACTER DRIVER STARTED ...\n\n");
	
	return SUCCESS;
}
void cleaning_function(void)
{
	cdev_del(&my_cdev);
	
	unregister_chrdev_region(dev, count);
	
	printk(KERN_INFO "CHARACTER DRIVER STOPPED..");
}

module_init(starting_function);
module_exit(cleaning_function);
