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
	@for src in $(SRCS) ; do \
		echo $$src; \
	done

list-obj:
	@for obj in $(OBJS) ; do \
		echo $$obj; \
	done

qemu: image
	qemu-system-i386.exe -boot c build/image.bin -gdb tcp::26000

clean:
	rm -rf build/
	rm -rf sysroot/
