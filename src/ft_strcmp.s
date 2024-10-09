; int strcmp(const char *s1, const char *s2);
section .text
	global ft_strcmp

ft_strcmp:
	; s1: rdi -  s2: rsi
	xor rbx, rbx ; init counter
	xor rax, rax ; init return register

_loop:
	mov cl, [rdi + rbx] ; cl = s1[rbx]
	mov dl, [rsi + rbx] ; dl = s2[rbx]
	cmp cl, 0 ; check if s1 is over
	jz _return
	cmp dl, 0 ; check if s2 is over
	jz _return
	mov al, cl
	sub al, dl
	cmp al, 0
	jne _return
	inc rbx
	jmp _loop

_return:
	mov al, cl
	sub al, dl
	movsx rax, al ; sign-extend al to rax
	ret

section .note.GNU-stack