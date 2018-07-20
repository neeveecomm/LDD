#ifndef __GPIO_CHAR_DRV_H__

typedef struct {
	unsigned int gpionum;
	unsigned int direction;
	unsigned int value;
}udoo_shield_led_t;

#define SHIELD_IOCTL_CMD 123

#define BLUE_LED_NUM 143
#define RED_LED_NUM 148
#define GREEN_LED_NUM 146

#endif
