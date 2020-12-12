
disk_load:
    pusha
    push %dx

    mov $0x02, %ah          // read sectors from drive
    mov %dh, %al          // read 16 sectors
    mov $0x00, %ch          // first cyllinder
    mov $0x02, %cl          // second sector after boot sector
    mov $0x00, %dh          // head number

    int $0x13               // BIOS interrupt to read disk
    jc disk_error
    
    pop %dx
    cmp %dh, %al
    jne sectors_error
    
    popa
    ret

disk_error:
    push %ax
    mov $msg_disk_error, %si
    call printfunc
    pop %ax
    jmp .

sectors_error:
    push %ax
    mov $msg_sectors_error, %si
    call printfunc
    pop %ax
    jmp .

msg_disk_error: .ascii "Disk read error", "\x0a", "\x0d", "\0"
msg_sectors_error: .ascii "Incorrect number of sectors read!", "\x0a", "\x0d", "\0"
