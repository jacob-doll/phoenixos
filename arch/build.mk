BOOT_SRCS= \
	$(wildcard arch/$(ARCH_TARGET)/boot/*.s)
BOOT_OBJS= \
	$(patsubst %.s, $(BUILD_DIR)/%.o, $(BOOT_SRCS))

CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)

CRT_OBJS= \
	$(BUILD_DIR)/arch/$(ARCH_TARGET)/crt/crti.o \
	$(BUILD_DIR)/arch/$(ARCH_TARGET)/crt/crtn.o \
	$(CRTBEGIN_OBJ) \
	$(CRTEND_OBJ)

KERNEL_SRCS+= \
	$(wildcard arch/$(ARCH_TARGET)/kernel/*.c)

OBJS+= \
	$(BOOT_OBJS) \
	$(CRT_OBJS) 

SRCS+= \
	$(BOOT_SRCS) 
	
$(BUILD_DIR)/arch/$(ARCH_TARGET)/boot/%.o: arch/$(ARCH_TARGET)/boot/%.s
	@mkdir -p $(@D)
	@$(AS) -o $@ $^

$(BUILD_DIR)/arch/$(ARCH_TARGET)/crt/%.o: arch/$(ARCH_TARGET)/crt/%.s
	@mkdir -p $(@D)
	@$(AS) -o $@ $^

$(BUILD_DIR)/arch/$(ARCH_TARGET)/kernel/%.o: arch/$(ARCH_TARGET)/kernel/%.c
	@mkdir -p $(@D)
	@$(CC) $(KERNEL_FLAGS) -c $^ -o $@ -std=gnu99 -ffreestanding $(CFLAGS)