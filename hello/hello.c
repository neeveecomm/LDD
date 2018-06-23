#include <linux/init.h>
#include <linux/module.h>

static int f = 10;
static int arr[10];
static int num = 10;

module_param(f, int, 0644);
module_param_array(arr, int, &num, 0644);
 
static int __init init_hello(void)
{
	int i;
	printk("Module is inserted\n");
	printk("variable f: %d\n", f);
	
	for(i = 0; i < 10; i++) {
		printk("arr[%d] == %d\n", i, arr[i]);
	}

	return 0;
}

static void __exit exit_hello(void)
{
	printk("Module is removed\n");
}

module_init(init_hello);
module_exit(exit_hello);
MODULE_LICENSE("GPL");
