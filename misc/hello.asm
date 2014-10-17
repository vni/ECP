; nasm -f hello.s
; ld -o hello hello.o

section .text
	global _start
_start:
	jmp JMP_1

REAL_START:
	mov	eax, 4
	mov	ebx, 1
	mov	ecx, [esp]
	mov	edx, 14
	int	0x80

	mov	eax, 1
	mov	ebx, 108
	int	0x80

JMP_1:	call REAL_START
	db "Hello, World!", 10
