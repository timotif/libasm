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
	dec rax ; decrease at the beginning of the loop 
	; sub rax, 4 ; decrease counter
	cmp rax, -1 ; compare to -1 because at 0 we still want to copy the last byte
	jge _loop
	mov rax, rbx ; return the dst
	ret

section .note.GNU-stack