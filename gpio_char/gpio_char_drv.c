#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include "gpio_char_drv.h"
//#include <linux/devt.h>

static dev_t dev;
#define DEV_CNT 4
static struct cdev chardev;
static int value;

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
	int ledval;
	int data = 0;

	ledval = gpio_get_value(BLUE_LED_NUM);
	if(ledval == 1)
		data |= 0x01;

	ledval = gpio_get_value(RED_LED_NUM);
	if(ledval == 1)
		data |= 0x02;

	ledval = gpio_get_value(GREEN_LED_NUM);
	if(ledval == 1)
		data |= 0x04;

	copy_to_user(buffer, (char *)&data, sizeof(data));

	return sizeof(data);
}

static ssize_t chardev_write(struct file *filep, const char *buffer, size_t cnt, loff_t *offp)
{
	int ledval;

	copy_from_user(&ledval, buffer, sizeof(int));


	//value = gpio_get_value(143);
	value = (ledval & 0x01) ? 0 : 1;
	gpio_set_value(BLUE_LED_NUM, value);

	value = (ledval & 0x02) ? 0 : 1;
	gpio_set_value(RED_LED_NUM, value);

	value = (ledval & 0x04) ? 0 : 1;
	gpio_set_value(GREEN_LED_NUM, value);

	return sizeof(int);
}

static long chardev_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
	udoo_shield_led_t led;
	printk("%s:%d Called\n", __func__, __LINE__);
	switch(cmd) {
	case SHIELD_IOCTL_CMD:
		copy_from_user(&led, (char *) arg, sizeof(udoo_shield_led_t));
		switch(led.gpionum) {
			case BLUE_LED_NUM:
			case RED_LED_NUM:
			case GREEN_LED_NUM:
				if(led.direction == 0) {
					gpio_direction_output(led.gpionum, led.value);
				}else{
					gpio_direction_input(led.gpionum);
				}
				break;
		}
		break; 
	}
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
	
	ret = gpio_request_one(BLUE_LED_NUM, GPIOF_DIR_OUT, "blue led");
	if(ret < 0) {
		goto handle_err;	
	}

	ret = gpio_request_one(RED_LED_NUM, GPIOF_DIR_OUT, "red led");
	if(ret < 0) {
		goto handle_err;	
	}

	ret = gpio_request_one(GREEN_LED_NUM, GPIOF_DIR_OUT, "green led");
	if(ret < 0) {
		goto handle_err;	
	}

	return 0;

handle_err:
	cdev_del(&chardev);
	unregister_chrdev_region(dev, DEV_CNT);
	return ret;
}

static void exit_chardev(void)
{
	gpio_free(BLUE_LED_NUM);
	gpio_free(RED_LED_NUM);
	gpio_free(GREEN_LED_NUM);
	printk("Module is removed\n");
	cdev_del(&chardev);

	unregister_chrdev_region(dev, DEV_CNT);
}

module_init(init_chardev);
module_exit(exit_chardev);
MODULE_LICENSE("GPL");
