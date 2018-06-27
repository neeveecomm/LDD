# Skeleton Character Linux Device Drivers samples

This contains the following of Linux Character Driver samples,
1. Simple character driver registration and unegister
2. cdev allocation and initialization
3. featured with file operations like open, read, write, close, ioctl

# To compile the kernel module

$ make

# To insert the kernel module

$ sudo insmod hello.ko

# To remove the kernel module

$ sudo rmmod hello 

# To read the data from the driver

$ cat /dev/udoocdev0

# To write the data into the driver

$ echo "data" > /dev/udoocdev0

# To compile the application

$ gcc -o capp capp.c

# To view the kernel log messages

$ dmesg
