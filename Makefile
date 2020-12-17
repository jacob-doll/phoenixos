TARGET=i686-elf
CC=$(TARGET)-gcc
AS=$(TARGET)-as
LD=$(TARGET)-ld

CFLAGS=-O2 -Wall -Wextra

BUILD_DIR=$(shell pwd)/build
ARCH_TARGET=x86
BOOT_TARGET=bios/$(ARCH_TARGET)
SYSROOT=$(shell pwd)/sysroot

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

image: $(BOOTLOADER_BIN) $(KERNEL_BIN)
	cat $^ > $(BUILD_DIR)/image.bin


list-src:
	echo $(SRCS)
	echo $(OBJS)

# grub: all
# 	mkdir -p isodir/boot/grub
# 	cp $(KERNEL_BIN) isodir/boot/kernel.bin
# 	cp grub.cfg isodir/boot/grub/grub.cfg
# 	grub-mkrescue -o jacobos.iso isodir

# qemu: grub
# 	qemu-system-i386.exe -cdrom jacobos.iso

qemu: image
	qemu-system-i386.exe -boot c build/image.bin -gdb tcp::26000

clean:
	rm -rf $(BUILD_DIR)

deep-clean: clean
	rm -rf isodir
	rm -rf sysroot
	rm -rf $(BUILD_DIR)
	rm jacobos.iso