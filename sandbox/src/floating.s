section .data
	x dd 3.14
	y dd 2.1
section .text
	global _start
_start:
	movss xmm0, [x]
	movss xmm1, [y]
	ucomiss xmm0, xmm1
	mov ebx, 0
	ja _greater
	jmp _end
_greater:
	mov ebx, 1
_end:
	mov eax, 1
	int 80h