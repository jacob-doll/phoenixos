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
KERNEL_FLAGS+= -D_KERNEL_VERBOSE

IMAGE=$(BUILD_DIR)/disk.img

-include kernel/build.mk
-include bootloader/bios/x86/build.mk

all: kernel boot

headers:
	@mkdir -p $(SYSROOT)/usr/include
	@cp -R --preserve=timestamps $(HEADERS) $(SYSROOT)/usr/include

kernel: headers $(KERNEL_BIN)

boot: $(BOOTLOADER_BIN)

image: $(IMAGE)

$(IMAGE): boot kernel
	dd if=/dev/zero of=$(IMAGE) bs=512 count=32
	dd if=$(BUILD_DIR)/boot.sys of=$(IMAGE) bs=512 conv=notrunc
	dd if=$(BUILD_DIR)/kernel.sys of=$(IMAGE) bs=512 obs=512 seek=6 conv=notrunc

list-src:
	@for src in $(SRCS) ; do \
		echo $$src; \
	done

list-obj:
	@for obj in $(OBJS) ; do \
		echo $$obj; \
	done

iso: all
	@mkdir -p $(SYSROOT)/boot
	@cp $(BOOTLOADER_BIN) $(SYSROOT)/boot/loader.sys
	@cp $(KERNEL_BIN) $(SYSROOT)/kernel.sys
	xorriso -as mkisofs -R -J -c boot/bootcat \
		-b boot/loader.sys -no-emul-boot -boot-load-size 4 -boot-info-table \
      	-o ./bootable.iso ./sysroot

run: iso
	qemu-system-i386.exe -monitor stdio -display sdl -cdrom bootable.iso

debug: iso
	qemu-system-i386.exe -monitor stdio -display sdl -cdrom bootable.iso -S -gdb tcp::26000

run-boot: $(IMAGE) all
	qemu-system-i386.exe -monitor stdio -display sdl -boot c build/boot.bin

debug-boot: boot
	qemu-system-i386.exe -monitor stdio -display sdl -boot c build/boot.bin -S -gdb tcp::26000

clean:
	rm -rf build/
	rm -rf sysroot/
