; • Write a function that converts the initial portion of the string pointed by str to int
; representation.
; • str is in a specific base given as a second parameter.
; • excepted the base rule, the function should work exactly like ft_atoi.
; • If there’s an invalid argument, the function should return 0. Examples of invalid
; arguments :
; ◦ base is empty or size of 1;
; ◦ base contains the same character twice ;
; ◦ base contains + or - or whitespaces;
; • Here’s how it should be prototyped :

; int ft_atoi_base(char *str, char *base);
;	*str		->	rdi
;	*base		->	rsi
;	return val	->	rax

section .text
	global ft_atoi_base
	extern ft_strlen

ft_atoi_base:
	mov r10, rdi	; r10: str
	mov rdi, rsi	; rdi: base
	call ft_strlen	; rax: base_len
	mov r11, rdi	; r11: base
	mov r12, rax	; r12: base_len
	xor rax, rax	; init result to 0
	mov rbx, -1		; init str counter
loop_str:
	inc rbx
	cmp byte [r10 + rbx], 0
	je return
	mov rcx, -1		; init base counter
	mov r13b, [r10 + rbx]
loop_base:
	inc rcx
	cmp byte [r11, rcx], 0
	je update_result
	cmp byte [r11 + rcx], r13b
	je update_result
	jmp loop_base
update_result:
	cmp rcx, r12
	jg error
	mul r12
	add rax, rcx
	jmp loop_str
error:
	mov rax, 0
return:
	ret

section .note.GNU-stack