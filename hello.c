// JUST a Hello World Program.

#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

static int starting_function(void)
{
	printk(KERN_INFO "\n\n\nHELLO, WORLD");
	return 0;
}
static void cleaning_function(void)
{
	printk(KERN_INFO "GOODBYE, CRUEL WORLD\n\n\n");
}

module_init(starting_function);
module_exit(cleaning_function);
