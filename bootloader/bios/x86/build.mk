BOOTLOADER_SRCS= \
	$(wildcard bootloader/bios/x86/*.s)
BOOTLOADER_OBJS= \
	$(patsubst %.s, $(BUILD_DIR)/%.o, $(BOOTLOADER_SRCS))

BOOTLOADER_BIN = $(BUILD_DIR)/boot.bin

$(BUILD_DIR)/bootloader/bios/x86/%.o: bootloader/bios/x86/%.s
	@mkdir -p $(@D)
	@$(AS) -o $@ $^

$(BOOTLOADER_BIN): $(BOOTLOADER_OBJS)
	@mkdir -p $(@D)
	@$(LD) -o $@ --oformat binary -e init -Ttext 0x7c00 $^