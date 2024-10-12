; int strcmp(const char *s1, const char *s2);
;	s1	-> rdi
;	s2	-> rsi

section .text
	global ft_strcmp

ft_strcmp:
	; s1: rdi -  s2: rsi
	xor rbx, rbx ; init counter

_loop:
	mov cl, [rdi + rbx] ; cl = s1[rbx]
	mov dl, [rsi + rbx] ; dl = s2[rbx]
	test cl, cl ; check if s1 is over
	jz _end
	test dl, dl ; check if s2 is over
	jz _end
	sub cl, dl
	jne _return
	inc rbx
	jmp _loop

_end:
	sub cl, dl ; update return value if a string is over

_return:
	movsx rax, cl ; sign-extend al to rax
	ret

section .note.GNU-stack