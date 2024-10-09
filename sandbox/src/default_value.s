section .data
	num db 3 dup(2) ; 3 bytes, each with value 2
section .text
	global _start

_start:
	mov ebx, [num]
	mov eax, 1
	int 80h