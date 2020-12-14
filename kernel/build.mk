KERNEL_SRCS+= $(wildcard kernel/*.c)
KERNEL_OBJS+= $(patsubst %.c, $(BUILD_DIR)/%.o, $(KERNEL_SRCS)) 

KERNEL_BIN = $(BUILD_DIR)/kernel.bin

OBJS+= $(KERNEL_OBJS)
SRCS+= $(KERNEL_SRCS)

HEADERS+= $(shell pwd)/kernel/include/.

$(BUILD_DIR)/kernel/%.o: kernel/%.c
	@mkdir -p $(@D)
	@$(CC) $(KERNEL_FLAGS) -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

$(KERNEL_BIN): $(OBJS)
	@mkdir -p $(@D) 
	@$(LD) -o $@ -Ttext 0x1800 $^ --oformat binary
	@# @$(CC) -T arch/$(ARCH_TARGET)/linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc
