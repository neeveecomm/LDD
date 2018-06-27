# Hello World Linux Device Drivers samples

This contains Hello World Linux Device Driver sample with the following,
1. Simply insert the kernel module with printk information to verify in dmesg
2. Simply remove the kernel module with printk information to verify in dmesg
3. Also it featured with passing parameters to kernel module. parameters are single integer and array of integers.

# To compile the kernel module

$ make

# To insert the kernel module

$ sudo insmod hello.ko

# To remove the kernel module

$ sudo rmmod hello 

# To view the kernel log messages

$ dmesg


