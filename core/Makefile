CONFIG_MODULE_SIG=n
CONFIG_MODULE_SIG_ALL=n


KERNEL_VERSION := $(shell uname -r)
KERNEL_MODULES := /lib/modules/$(KERNEL_VERSION)/build

obj-m += chardev.o

all:
	$(MAKE) -C $(KERNEL_MODULES) M=$(shell pwd) modules
	
clean:
	$(MAKE) -C /$(KERNEL_MODULES) M=$(shell pwd) clean
	
test:
	$(MAKE) -C /$(KERNEL_MODULES) M=$(shell pwd) modules_install

load: all
	sudo insmod chardev.ko
	sudo dmesg -c
	
unload:
	sudo rmmod chardev.ko
	sudo dmesg -c
