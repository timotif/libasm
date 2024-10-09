; size_t strlen(const char *s)
section .text
	global ft_strlen

ft_strlen:
	xor rax, rax ; init counter
	jmp _loop;

_loop:
	cmp BYTE [rdi + rax], 0 ; BYTE specifies the size of the operand being accessed
	je _return
	inc rax
	jmp _loop

_return:
	ret

section .note.GNU-stack