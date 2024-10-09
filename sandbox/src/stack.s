section .text
	global _start

addtwo:
	push rbp ; save on the stack 
	mov rbp, rsp
	mov eax, [rbp + 16]
	mov ebx, [rbp + 24]
	add eax, ebx
	pop rbp
	ret

_start:
	push 22
	push 20
	call addtwo
	mov ebx, eax ; preserve the result
	mov eax, 1
	int 0x80