; char *stpcpy(char *restrict dst, const char *restrict src);
;	dst		-> rdi
;	src		-> rsi

section .text
	global ft_strcpy
	extern ft_strlen

; First approach
; ft_strcpy:
; 	mov rbx, rdi ; save to rbx the first arg: dst
; 	mov rdi, rsi ; move to rdi the src so that it's the arg for ft_strlen
; 	call ft_strlen ; call ft_strlen on the src
; 	; rax contains the length of the src
; 	; rdi contains the dst
; 	; rsi contains the src
; 
; _loop:
;     mov cl, [rsi + rax]  ; load the byte from src into cl
;     mov [rbx + rax], cl  ; store the byte into dst
; 	cmp rax, 0 ; compare to 0
; 	je _return
; 	dec rax ; decrease after the check to avoid rax to ever go negative (invalid read)
; 	jmp _loop
; _return:
; 	mov rax, rbx ; return the dst
; 	ret

; Better approach using movsb (42% improvement on a 4MB-long string)
ft_strcpy:
	mov rbx, rdi ; save away rdi
	mov rdi, rsi ; set source string as arg for strlen
	call ft_strlen
	mov rdi, rbx ; get back rdi original content
	mov rcx, rax ; set the counter for rep on the return value of strlen
	inc rcx ; include null terminator
	rep movsb ; move a byte from rsi to rdi rcx times
	mov rax, rbx ; set return value to the original dst value
	ret

section .note.GNU-stack