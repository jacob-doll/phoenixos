
/// PRINT
printfunc:
    lodsb
    or %al, %al
    jz .end
    mov $0x0e, %ah
    int $0x10
    jmp printfunc
.end:
    ret
