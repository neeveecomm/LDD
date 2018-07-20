#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "gpio_char_drv.h"

int main(int argc, char *argv[])
{
	int fd, ret, value;	
	char buf[64] = "hari";
	char rdbuf[64];
	int cnt = 0;
	fd = open(argv[1], O_RDWR);
	if(fd < 0) {
		perror("Open Failed");
		return -1;
	}

	do {
		udoo_shield_led_t led;

		led.gpionum = BLUE_LED_NUM;
		if(cnt & 0x01) {
			led.value = 0;
		}else{
			led.value = 1;
		}

		ret = ioctl(fd, SHIELD_IOCTL_CMD, (unsigned long)&led);
		if(ret < 0) {
			perror("write failed\n");
			return -1;
		}

		led.gpionum = RED_LED_NUM;
		if(cnt & 0x02) {
			led.value = 0;
		}else{
			led.value = 1;
		}

		ret = ioctl(fd, SHIELD_IOCTL_CMD, (unsigned long)&led);
		if(ret < 0) {
			perror("write failed\n");
			return -1;
		}

		led.gpionum = GREEN_LED_NUM;
		if(cnt & 0x04) {
			led.value = 0;
		}else{
			led.value = 1;
		}

		ret = ioctl(fd, SHIELD_IOCTL_CMD, (unsigned long)&led);
		if(ret < 0) {
			perror("write failed\n");
			return -1;
		}

		sleep(1);
		cnt++;
	} while(1);

	do {
		ret = write(fd, buf, strlen(buf));	
		if(ret < 0) {
			perror("write failed\n");
			return -1;
		}
		printf("Write succes : %d bytes\n", ret);
		sleep(1);
	}while(1);


	ret = read(fd, &value, 4);
	if(ret < 0) {
		perror("read failed\n");
		return -1;
	}
	printf("Read succes : %d GPIO Data: %d\n", ret, value);

	close(fd);
	return 0;
}
