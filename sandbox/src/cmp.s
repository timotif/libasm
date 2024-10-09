section .text
	global _start

_start:
	mov eax, 42
	mov ebx, 69
	cmp eax, ebx
	jl _less_than
	jmp end

_less_than:
	mov ecx, 1
	mov ebx, 1

end:
	mov eax, 1
	int 80h