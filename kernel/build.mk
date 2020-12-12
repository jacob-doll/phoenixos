KERNEL_SRCS+= $(wildcard kernel/*.c)
KERNEL_OBJS+= $(patsubst %.c, $(BUILD_DIR)/%.o, $(KERNEL_SRCS)) 

KERNEL_BIN = $(BUILD_DIR)/kernel.bin

OBJS+= $(KERNEL_OBJS)
SRCS+= $(KERNEL_SRCS)

HEADERS+= $(shell pwd)/kernel/include/.

$(BUILD_DIR)/kernel/%.o: kernel/%.c
	@mkdir -p $(@D)
	@$(CC) -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

$(KERNEL_BIN): $(OBJS)
	@mkdir -p $(@D)
	# @$(CC) -T arch/$(ARCH_TARGET)/linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc
	@$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary