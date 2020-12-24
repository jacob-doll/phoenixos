.extern isr_handler

.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31

.section .text
_isr_common_stub:
    pusha
    call isr_handler
    popa
    add $8, %esp
    iret

# 0: Divide By Zero Exception
isr0:
    cli
    push $0
    push $0
    jmp _isr_common_stub

# 1: Debug Exception
isr1:
    cli
    push $0
    push $1
    jmp _isr_common_stub

# 2: Non Maskable Interrupt Exception
isr2:
    cli
    push $0
    push $2
    jmp _isr_common_stub

# 3: Int 3 Exception
isr3:
    cli
    push $0
    push $3
    jmp _isr_common_stub

# 4: INTO Exception
isr4:
    cli
    push $0
    push $4
    jmp _isr_common_stub

# 5: Out of Bounds Exception
isr5:
    cli
    push $0
    push $5
    jmp _isr_common_stub

# 6: Invalid Opcode Exception
isr6:
    cli
    push $0
    push $6
    jmp _isr_common_stub

# 7: Coprocessor Not Available Exception
isr7:
    cli
    push $0
    push $7
    jmp _isr_common_stub

# 8: Double Fault Exception (With Error Code!)
isr8:
    cli
    push $8
    jmp _isr_common_stub

# 9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push $0
    push $9
    jmp _isr_common_stub

# 10: Bad TSS Exception (With Error Code!)
isr10:
    cli
    push $10
    jmp _isr_common_stub

# 11: Segment Not Present Exception (With Error Code!)
isr11:
    cli
    push $11
    jmp _isr_common_stub

# 12: Stack Fault Exception (With Error Code!)
isr12:
    cli
    push $12
    jmp _isr_common_stub

# 13: General Protection Fault Exception (With Error Code!)
isr13:
    cli
    push $13
    jmp _isr_common_stub

# 14: Page Fault Exception (With Error Code!)
isr14:
    cli
    push $14
    jmp _isr_common_stub

# 15: Reserved Exception
isr15:
    cli
    push $0
    push $15
    jmp _isr_common_stub

# 16: Floating Point Exception
isr16:
    cli
    push $0
    push $16
    jmp _isr_common_stub

# 17: Alignment Check Exception
isr17:
    cli
    push $0
    push $17
    jmp _isr_common_stub

# 18: Machine Check Exception
isr18:
    cli
    push $0
    push $18
    jmp _isr_common_stub

# 19: Reserved
isr19:
    cli
    push $0
    push $19
    jmp _isr_common_stub

# 20: Reserved
isr20:
    cli
    push $0
    push $20
    jmp _isr_common_stub

# 21: Reserved
isr21:
    cli
    push $0
    push $21
    jmp _isr_common_stub

# 22: Reserved
isr22:
    cli
    push $0
    push $22
    jmp _isr_common_stub

# 23: Reserved
isr23:
    cli
    push $0
    push $23
    jmp _isr_common_stub

# 24: Reserved
isr24:
    cli
    push $0
    push $24
    jmp _isr_common_stub

# 25: Reserved
isr25:
    cli
    push $0
    push $25
    jmp _isr_common_stub

# 26: Reserved
isr26:
    cli
    push $0
    push $26
    jmp _isr_common_stub

# 27: Reserved
isr27:
    cli
    push $0
    push $27
    jmp _isr_common_stub

# 28: Reserved
isr28:
    cli
    push $0
    push $28
    jmp _isr_common_stub

# 29: Reserved
isr29:
    cli
    push $0
    push $29
    jmp _isr_common_stub

# 30: Reserved
isr30:
    cli
    push $0
    push $30
    jmp _isr_common_stub

# 31: Reserved
isr31:
    cli
    push $0
    push $31
    jmp _isr_common_stub