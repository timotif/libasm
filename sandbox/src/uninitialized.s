section .bss ; bss = block starting symbol, used for reserving space in memory
	num resb 3 ; reserve 3 bytes

section .text
	global _start

_start:
	mov bl, 1
	mov [num], bl
	mov [num+1], bl
	mov [num+2], bl
	mov eax, 1
	int 80h
