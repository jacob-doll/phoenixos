/* x86 crtn.s */
.section .init
	popl %ebp
	ret

.section .fini
	popl %ebp
	ret
