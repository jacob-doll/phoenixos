BOOT_SRCS= \
	$(wildcard kernel/arch/$(ARCH_TARGET)/boot/*.S)
BOOT_OBJS= \
	$(patsubst %.s, $(BUILD_DIR)/%.o, $(BOOT_SRCS))

CRTBEGIN_OBJ:= \
	$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:= \
	$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)

CRT_OBJS= \
	$(BUILD_DIR)/kernel/arch/$(ARCH_TARGET)/crt/crti.o \
	$(BUILD_DIR)/kernel/arch/$(ARCH_TARGET)/crt/crtn.o \
	$(CRTBEGIN_OBJ) \
	$(CRTEND_OBJ)

KERNEL_SRCS+= \
	$(wildcard kernel/arch/$(ARCH_TARGET)/kernel/*.c) \
	$(wildcard kernel/*.c)

KERNEL_ASM_SRCS+= \
	$(wildcard kernel/arch/$(ARCH_TARGET)/kernel/*.S) 

KERNEL_OBJS= \
	$(patsubst %.c, $(BUILD_DIR)/%.o, $(KERNEL_SRCS)) \
	$(patsubst %.S, $(BUILD_DIR)/%.S.o, $(KERNEL_ASM_SRCS))

OBJS+= \
	$(BOOT_OBJS) \
	$(CRT_OBJS) \
	$(KERNEL_OBJS)

SRCS+= \
	$(BOOT_SRCS) \
	$(KERNEL_SRCS)
	
HEADERS+= $(shell pwd)/kernel/include/.

KERNEL_ELF = $(BUILD_DIR)/kernel.elf
KERNEL_BIN = $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel/arch/$(ARCH_TARGET)/boot/%.o: kernel/arch/$(ARCH_TARGET)/boot/%.s
	@mkdir -p $(@D)
	@#$(AS) -o $@ $^
	$(CC) -c $^ -o $@

$(BUILD_DIR)/kernel/arch/$(ARCH_TARGET)/crt/%.o: kernel/arch/$(ARCH_TARGET)/crt/%.s
	@mkdir -p $(@D)
	@#$(AS) -o $@ $^
	$(CC) -c $^ -o $@

$(BUILD_DIR)/kernel/arch/$(ARCH_TARGET)/kernel/%.o: kernel/arch/$(ARCH_TARGET)/kernel/%.c
	@mkdir -p $(@D)
	$(CC) $(KERNEL_FLAGS) -c $^ -o $@ -std=gnu99 -ffreestanding $(CFLAGS)

$(BUILD_DIR)/kernel/arch/$(ARCH_TARGET)/kernel/%.S.o: kernel/arch/$(ARCH_TARGET)/kernel/%.S
	@mkdir -p $(@D)
	$(CC) $(KERNEL_FLAGS) -c $^ -o $@ -std=gnu99 -ffreestanding $(CFLAGS)

$(BUILD_DIR)/kernel/%.o: kernel/%.c
	@mkdir -p $(@D)
	$(CC) $(KERNEL_FLAGS) -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

$(KERNEL_ELF): $(OBJS)
	@mkdir -p $(@D) 
	@#$(LD) -o $@ -Ttext 0x1800 $^ --oformat binary
	$(CC) -T kernel/arch/$(ARCH_TARGET)/linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc

$(KERNEL_BIN): $(KERNEL_ELF)
	objcopy -O binary $^ $@
