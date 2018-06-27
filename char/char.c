#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

//#include <linux/devt.h>

static dev_t dev;
#define DEV_CNT 4
static struct cdev chardev;

static int chardev_open(struct inode *nodep, struct file *filep)
{
	printk("%s:%d Called\n", __func__, __LINE__);
	return 0;
}

static int chardev_release(struct inode *nodep, struct file *filep)
{
	printk("%s:%d Called\n", __func__, __LINE__);
	return 0;
}

static ssize_t chardev_read(struct file *filep, char *buffer, size_t cnt, loff_t *offp)
{
	static int rdcnt = 0;

	char kbuf[64] = "udoocdev\n";

	copy_to_user(buffer, kbuf, 10);

	printk("%s:%d Called\n", __func__, __LINE__);
	rdcnt++;
	if(rdcnt == 10) {
		rdcnt =0;
		return 0;
	}

	return 10;
}

static ssize_t chardev_write(struct file *filep, const char *buffer, size_t cnt, loff_t *offp)
{
	char kbuf[64];
	memset(kbuf, 0, 64);
	copy_from_user(kbuf, buffer, cnt);

	printk("%s:%d Data: %s\n", __func__, __LINE__, kbuf);

	return cnt;
}

static long chardev_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
	printk("%s:%d Called\n", __func__, __LINE__);
	return 0;
}

static struct file_operations chardev_fops = {
	.owner = THIS_MODULE,
	.open = chardev_open,
	.release = chardev_release,
	.read = chardev_read,
	.write = chardev_write,
	.unlocked_ioctl = chardev_ioctl
};

static int init_chardev(void)
{
	int ret;
	printk("Module is inserted\n");

	ret = alloc_chrdev_region(&dev, 0, DEV_CNT, "udoocdev");
	if(ret != 0) {
		printk("Allocate char dev region is failed\n");
		return ret;
	}

	cdev_init(&chardev, &chardev_fops);
	cdev_add(&chardev, dev, DEV_CNT);

	return 0;
}

static void exit_chardev(void)
{
	printk("Module is removed\n");
	cdev_del(&chardev);

	unregister_chrdev_region(dev, DEV_CNT);
}

module_init(init_chardev);
module_exit(exit_chardev);
MODULE_LICENSE("GPL");
