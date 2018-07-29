# Simple Linux Input Device Drivers Sample

This contains the following of Linux Input Driver samples,
1. Input device driver registeration and unregistration
2. Request Interrupt handling and de-registering the interrupts.
3. Input event generation for key press and release events

# To compile the kernel module

$ make

# To insert the kernel module

$ sudo insmod udoo_input.ko

# To remove the kernel module

$ sudo rmmod udoo_input

# To test the data from the driver

$ evtest /dev/input/eventX

# To view the kernel log messages

$ dmesg
