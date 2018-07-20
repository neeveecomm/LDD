# Simple Linux Character Driver for GPIO Access

This contains the following of Linux Character Driver GPIO samples,
1. Simple character driver used to access the GPIO
2. configure the GPIO as input / output
3. Read, Write, from GPIO. IOCTL over the GPIO Direction.

# To compile the kernel module

$ make

# To insert the kernel module

$ sudo insmod gpio_char_drv.ko

# To remove the kernel module

$ sudo rmmod gpio_char_drv 

# To compile the application

$ gcc -o app_gpio app_gpio.c

$ gcc -o app_gpio_output app_gpio_output.c

$ gcc -o app_gpio_input app_gpio_input.c

# To run the application

./app_gpio /dev/udoocdev0

./app_gpio_output /dev/udoocdev0

./app_gpio_input /dev/udoocdev0


# To view the kernel log messages

$ dmesg
