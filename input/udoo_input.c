#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>

#define UDOO_GPIO 	120
#define MUX_D		118
#define MUX_E		114
#define MUX_F		115

static struct input_dev *udoo_dev;

static struct gpio adc_mux[3] = {
	{MUX_D, GPIOF_OUT_INIT_HIGH, "MUX_D"},
	{MUX_E, GPIOF_OUT_INIT_HIGH, "MUX_E"},
	{MUX_F, GPIOF_OUT_INIT_HIGH, "MUX_F"},
};

static irqreturn_t udoo_isr(int num, void *data)
{
	struct input_dev *idev = (struct input_dev *)data;
	int state = gpio_get_value_cansleep(UDOO_GPIO) ? 1 : 0;

	input_event(udoo_dev, EV_KEY, BTN_RIGHT, state);
	input_sync(udoo_dev); 

	return IRQ_HANDLED;
}

static int input_dev_init(void)
{
	int ret;
	
	ret = gpio_request_one(UDOO_GPIO, GPIOF_DIR_IN, "UDOO GPIO");
	if(ret < 0) {
		printk("GPIO Request Failed\n");
		return -1;
	}

	ret = gpio_request_array(adc_mux, ARRAY_SIZE(adc_mux));
	if(ret < 0) {
		printk("gpio request array failed\n");
		goto ret_err1;
	}
	
	udoo_dev = input_allocate_device();
	if(udoo_dev == NULL) {
		printk("input device allocate failed\n");
		goto ret_err1;
	}

	ret = request_irq(gpio_to_irq(UDOO_GPIO), udoo_isr, IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING | IRQF_SHARED, "UDOO_INTR", (void *)udoo_dev);
	if(ret < 0) {
		printk("IRQ Request Failed\n");
		goto ret_err2;
	}

	udoo_dev->name = "udoo";

	udoo_dev->evbit[0] = BIT_MASK(EV_KEY);
	udoo_dev->keybit[BIT_WORD(BTN_RIGHT)] = BIT_MASK(BTN_RIGHT);
	
	ret = input_register_device(udoo_dev);
	if(ret < 0) {
		printk("input register device failed\n");
		goto ret_err3;
	}
	return 0;

ret_err3:
	free_irq(gpio_to_irq(UDOO_GPIO), (void *)udoo_dev);	
ret_err2:
	input_free_device(udoo_dev);	
ret_err1:
	gpio_free_array(adc_mux, ARRAY_SIZE(adc_mux));
ret_err:
	gpio_free(UDOO_GPIO);
	return -1;
}

static void input_dev_exit(void)
{
	input_unregister_device(udoo_dev);
	free_irq(gpio_to_irq(UDOO_GPIO), (void *)udoo_dev);
	gpio_free_array(adc_mux, ARRAY_SIZE(adc_mux));
	input_free_device(udoo_dev);
	gpio_free(UDOO_GPIO);
}

module_init(input_dev_init);
module_exit(input_dev_exit);
MODULE_LICENSE("GPL");
