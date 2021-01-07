BOOT_SRCS= \
	$(wildcard kernel/arch/$(ARCH_TARGET)/boot/*.S)
BOOT_OBJS= \
	$(patsubst %.S, $(BUILD_DIR)/%.o, $(BOOT_SRCS))

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
	$(wildcard kernel/arch/$(ARCH_TARGET)/*.c) \
	$(wildcard kernel/*.c)

KERNEL_ASM_SRCS+= \
	$(wildcard kernel/arch/$(ARCH_TARGET)/*.S) 

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

KERNEL_BIN = $(BUILD_DIR)/kernel.sys

$(BUILD_DIR)/$(ARCH_DIR)/boot/%.o: $(ARCH_DIR)/boot/%.S
	@mkdir -p $(@D)
	$(CC) $(KERNEL_FLAGS) -c $^ -o $@ -std=gnu99 -ffreestanding $(CFLAGS) -I$(ARCH_DIR)/include

$(BUILD_DIR)/$(ARCH_DIR)/crt/%.o: $(ARCH_DIR)/crt/%.s
	@mkdir -p $(@D)
	$(CC) $(KERNEL_FLAGS) -c $^ -o $@ -std=gnu99 -ffreestanding $(CFLAGS)

$(BUILD_DIR)/$(ARCH_DIR)/%.o: $(ARCH_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(KERNEL_FLAGS) -c $^ -o $@ -std=gnu99 -ffreestanding $(CFLAGS) -I$(ARCH_DIR)/include

$(BUILD_DIR)/$(ARCH_DIR)/%.S.o: $(ARCH_DIR)/%.S
	@mkdir -p $(@D)
	$(CC) $(KERNEL_FLAGS) -c $^ -o $@ -std=gnu99 -ffreestanding $(CFLAGS) -I$(ARCH_DIR)/include

$(BUILD_DIR)/kernel/%.o: kernel/%.c
	@mkdir -p $(@D)
	$(CC) $(KERNEL_FLAGS) -c $< -o $@ -std=gnu99 -ffreestanding $(CFLAGS)

$(KERNEL_BIN): $(OBJS)
	@mkdir -p $(@D) 
	$(CC) -T kernel/arch/$(ARCH_TARGET)/linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc
