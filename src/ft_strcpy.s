section .text
	global ft_strcpy
	extern ft_strlen

ft_strcpy:
	mov rbx, rdi ; save to rbx the first arg: dst
	mov rdi, rsi ; move to rdi the src so that it's the arg for ft_strlen
	call ft_strlen ; call ft_strlen on the src
	; rax contains the length of the src
	; rdi contains the dst
	; rsi contains the src

_loop:
    mov cl, [rsi + rax]  ; load the byte from src into cl
    mov [rbx + rax], cl  ; store the byte into dst
	cmp rax, 0 ; compare to 0
	je _return
	dec rax ; decrease after the check to avoid rax to ever go negative (invalid read)
	jmp _loop
_return:
	mov rax, rbx ; return the dst
	ret

section .note.GNU-stack