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

# To read the data from the driver

$ cat /dev/udoocdev0

# To write the data into the driver

$ echo "data" > /dev/udoocdev0

# To compile the application

$ gcc -o app_gpio app_gpio.c
$ gcc -o app_gpio_output app_gpio_output.c
$ gcc -o app_gpio_input app_gpio_input.c

# To view the kernel log messages

$ dmesg
