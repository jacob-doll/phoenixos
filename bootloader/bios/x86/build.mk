# BOOTSECT_SRC= \
# 	bootloader/$(BOOT_TARGET)/bootsect/boot.S
# BOOTSECT_OBJ= \
# 	$(patsubst %.S, $(BUILD_DIR)/%.S.o, $(BOOTSECT_SRC))
# BOOTSECT_INC= \
# 	$(wildcard bootloader/$(BOOT_TARGET)/bootsect/*.inc)

# BOOTLOADER_BIN = $(BUILD_DIR)/boot.bin

# $(BOOTSECT_OBJ): $(BOOTSECT_SRC) $(BOOTSECT_INC)
# 	@mkdir -p $(@D)
# 	$(CC) -c $(BOOTSECT_SRC) -o $@

# $(BOOTLOADER_BIN): $(BOOTSECT_OBJ)
# 	@mkdir -p $(@D)
# 	$(LD) -o $@ --oformat binary -e _start -Ttext 0x7c00 $^

BOOTSECT_DIR= \
	bootloader/$(BOOT_TARGET)/bootsect
BOOTSECT_INC= \
	$(wildcard $(BOOTSECT_DIR)/*.inc)

STAGE2_ASM_SRCS= \
	$(wildcard bootloader/$(BOOT_TARGET)/stage2/*.S)
STAGE2_SRCS= \
	$(wildcard bootloader/$(BOOT_TARGET)/stage2/*.c)
STAGE2_OBJS= \
	$(patsubst %.S, $(BUILD_DIR)/%.S.o, $(STAGE2_ASM_SRCS)) \
	$(patsubst %.c, $(BUILD_DIR)/%.o, $(STAGE2_SRCS))

BOOTSECT_BIN= $(BUILD_DIR)/bootsect.bin
STAGE2_BIN= $(BUILD_DIR)/stage2.bin
BOOTLOADER_BIN= $(BUILD_DIR)/boot.bin

$(BUILD_DIR)/$(BOOTSECT_DIR)/boot.S.o: $(BOOTSECT_DIR)/boot.S $(BOOTSECT_INC)
	@mkdir -p $(@D)
	$(CC) -c $(BOOTSECT_DIR)/boot.S -o $@

$(BOOTSECT_BIN): $(BUILD_DIR)/$(BOOTSECT_DIR)/boot.S.o
	@mkdir -p $(@D)
	$(LD) -o $@ --oformat binary -e _start -Ttext 0x7c00 $^

bootsect: $(BOOTSECT_BIN)

$(BUILD_DIR)/bootloader/$(BOOT_TARGET)/stage2/%.S.o: bootloader/$(BOOT_TARGET)/stage2/%.S
	@mkdir -p $(@D)
	$(CC) -c $^ -o $@ -std=gnu99 -ffreestanding $(CFLAGS)

$(BUILD_DIR)/bootloader/$(BOOT_TARGET)/stage2/%.o: bootloader/$(BOOT_TARGET)/stage2/%.c
	@mkdir -p $(@D)
	$(CC) -c $^ -o $@ -std=gnu99 -ffreestanding $(CFLAGS)

$(STAGE2_BIN): $(STAGE2_OBJS)
	@mkdir -p $(@D)
	$(CC) -T bootloader/$(BOOT_TARGET)/stage2/linker.ld -o $(BUILD_DIR)/stage2.elf -ffreestanding -O2 -nostdlib $^ -lgcc
	objcopy -O binary $(BUILD_DIR)/stage2.elf $@

stage2: $(STAGE2_BIN)

$(BOOTLOADER_BIN) : $(BOOTSECT_BIN) $(STAGE2_BIN)
	python3 bootloader/$(BOOT_TARGET)/bootloader.py $@ $^
