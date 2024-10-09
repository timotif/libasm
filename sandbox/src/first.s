section .data
section .text
	global _start

_start:
	mov eax, 1 ; what system call
	mov ebx, 42 ; status code
	int 80h ; h for hex