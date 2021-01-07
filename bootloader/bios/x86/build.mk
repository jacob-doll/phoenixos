BOOT_ASM_SRCS= \
	$(wildcard bootloader/$(BOOT_TARGET)/*.S)
BOOT_SRCS= \
	$(wildcard bootloader/$(BOOT_TARGET)/*.c)
BOOT_OBJS= \
	$(patsubst %.S, $(BUILD_DIR)/%.S.o, $(BOOT_ASM_SRCS)) \
	$(patsubst %.c, $(BUILD_DIR)/%.o, $(BOOT_SRCS))

BOOT_BIN= $(BUILD_DIR)/boot.bin
BOOTLOADER_BIN= $(BUILD_DIR)/boot.sys

$(BUILD_DIR)/bootloader/$(BOOT_TARGET)/%.S.o: bootloader/$(BOOT_TARGET)/%.S
	@mkdir -p $(@D)
	$(CC) -c $^ -o $@ -std=gnu99 -ffreestanding $(CFLAGS)

$(BUILD_DIR)/bootloader/$(BOOT_TARGET)/%.o: bootloader/$(BOOT_TARGET)/%.c
	@mkdir -p $(@D)
	$(CC) -c $^ -o $@ -std=gnu99 -ffreestanding $(CFLAGS)

$(BOOT_BIN): $(BOOT_OBJS)
	@mkdir -p $(@D)
	$(CC) -T bootloader/$(BOOT_TARGET)/linker.ld -o $(BUILD_DIR)/boot.elf -ffreestanding -O2 -nostdlib $^ -lgcc
	objcopy -O binary $(BUILD_DIR)/boot.elf $@

$(BOOTLOADER_BIN) : $(BOOT_BIN)
	python3 bootloader/$(BOOT_TARGET)/bootloader.py $@ $^
