section .data
; need to create variable name, type (size), and value
	num dd 5 ; allocates on the stack
	; db = define byte (1 byte), dw = define word (2 bytes), dd = define double word (4 bytes), dq = define quad word (8 bytes), dt = define ten bytes (10 bytes)

section .text
	global _start

_start:
	mov eax, 1
	mov ebx, [num] ; dereference the variable with []
	int 80h