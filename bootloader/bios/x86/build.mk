BOOTLOADER_SRCS= \
	$(wildcard bootloader/bios/x86/*.S)
BOOTLOADER_OBJS= \
	$(patsubst %.S, $(BUILD_DIR)/%.o, $(BOOTLOADER_SRCS))

BOOTLOADER_BIN = $(BUILD_DIR)/boot.bin

$(BUILD_DIR)/bootloader/bios/x86/%.o: bootloader/bios/x86/%.S
	@mkdir -p $(@D)
	@$(CC) -c $^ -o $@

$(BOOTLOADER_BIN): $(BOOTLOADER_OBJS)
	@mkdir -p $(@D)
	@$(LD) -o $@ --oformat binary -e init -Ttext 0x7c00 $^