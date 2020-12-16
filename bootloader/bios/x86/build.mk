BOOTSECT_SRC= \
	bootloader/$(BOOT_TARGET)/bootsect/bootsect.S
BOOTSECT_OBJ= \
	$(patsubst %.S, $(BUILD_DIR)/%.o, $(BOOTSECT_SRC))
BOOTSECT_INC= \
	$(wildcard bootloader/$(BOOT_TARGET)/bootsect/*.inc)

BOOTLOADER_BIN = $(BUILD_DIR)/boot.bin

$(BOOTSECT_OBJ): $(BOOTSECT_SRC) $(BOOTSECT_INC)
	@mkdir -p $(@D)
	@$(CC) -c $(BOOTSECT_SRC) -o $@

$(BOOTLOADER_BIN): $(BOOTSECT_OBJ)
	@mkdir -p $(@D)
	@$(LD) -o $@ --oformat binary -e _start -Ttext 0x7c00 $^