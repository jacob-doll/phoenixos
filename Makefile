TARGET=i686-elf
CC=$(TARGET)-gcc
AS=$(TARGET)-as
LD=$(TARGET)-ld

CFLAGS=-O2 -Wall -Wextra

ARCH_TARGET=x86
BOOT_TARGET=bios/$(ARCH_TARGET)
SYSROOT=$(shell pwd)/sysroot

BUILD_DIR=$(shell pwd)/build
ARCH_DIR=kernel/arch/$(ARCH_TARGET)

KERNEL_FLAGS+= --sysroot=$(SYSROOT)
KERNEL_FLAGS+= -isystem=/usr/include

# -include arch/build.mk
-include kernel/build.mk
-include bootloader/bios/x86/build.mk

all: kernel boot

headers:
	@mkdir -p $(SYSROOT)/usr/include
	@cp -R --preserve=timestamps $(HEADERS) $(SYSROOT)/usr/include

kernel: headers $(KERNEL_BIN)

boot: $(BOOTLOADER_BIN)

image: boot kernel
	dd if=/dev/zero of=$(BUILD_DIR)/disk.img bs=512 count=20
	dd if=$(BUILD_DIR)/boot.bin of=$(BUILD_DIR)/disk.img bs=512 conv=notrunc
	dd if=$(BUILD_DIR)/kernel.bin of=$(BUILD_DIR)/disk.img bs=512 obs=512 seek=1 conv=notrunc

list-src:
	@for src in $(SRCS) ; do \
		echo $$src; \
	done

list-obj:
	@for obj in $(OBJS) ; do \
		echo $$obj; \
	done

run: image
	qemu-system-i386.exe -boot c build/disk.img

debug: image
	qemu-system-i386.exe -boot c build/disk.img -S -gdb tcp::26000

clean:
	rm -rf build/
	rm -rf sysroot/
