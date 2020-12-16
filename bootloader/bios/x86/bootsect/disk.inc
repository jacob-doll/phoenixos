
disk_load:
    pusha

    mov $0x42, %ah
    mov (disk_drive), %dl
    mov $DAP_struct, %si

    movw $0x10,       (%si)    // size of DAP (16 bytes)
    mov %dh,          2(%si)   // number of sectors to read
    movw %bx,         4(%si)   // offset
    movw %es,         6(%si)   // segment
    movl $0x00000001, 8(%si)   // start sector
    movl $0x00000000, 12(%si)  // (cont. )

    int $0x13
    jc fatal_error

    popa
    ret

/*
 * DAP (Disk Address Packet) buffer
 */
.equ DAP_struct, 0x8000
