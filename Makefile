# MUST be renamed to 'Makefile' in the same working directory
# as the kernel module to function correctly (on Debian at least)

obj-m += hello.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
		$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
		$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
