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

section .bss
	bitmap resb 32 ; 256-bit bitmap (32 bytes)

section .text
	global ft_atoi_base
	extern ft_strlen

ft_atoi_base:
	mov r10, rdi	; r10: str
	mov rdi, rsi	; rdi: base
	call ft_strlen	; rax: base_len
	mov r12, rax	; r12: base_len
	mov r11, rdi	; r11: base
base_validation:
	cmp rax, 2
	jl error
	call ft_find_duplicates
	cmp rax, 1
	je error
init:
	xor rax, rax	; init result to 0
	mov rbx, -1		; init str counter
loop_str:			; outer loop
	inc rbx
	cmp byte [r10 + rbx], 0
	je return
	mov rcx, -1		; init base counter
	mov r13b, [r10 + rbx]
loop_base:			; inner loop
	inc rcx
	cmp byte [r11, rcx], 0
	je update_result
	cmp byte [r11 + rcx], r13b
	je update_result
	jmp loop_base
update_result:
	cmp rcx, r12
	jge error
	mul r12
	add rax, rcx
	jmp loop_str
error:
	mov rax, 0
return:
	ret

; int ft_find_duplicates(char *base)
; 	rdi		-> base
; 	returns 	0 if no duplicates
;				1 if duplicates
ft_find_duplicates:
	; init bitmap
	mov rcx, 4				; num of bytes
	lea rsi, [rel bitmap]		; move bitmap address to rsi
	xor rax, rax			; rax = 0
	rep mov dword [rsi + rcx], 0				; repeat storing al into [rdi] rcx times
	xor rcx, rcx			; init counter
check_dup_loop:	
	mov al, [rdi + rcx]		; load current char
	test al, al				; check if it reached the end
	jz no_duplicates	
	movzx rbx, al			; zero extend	
	shr rbx, 3				; find byte index by dividing by 8
	and al, 7				; find bit inside the byte
	movzx rdx, al
	; Check bitmap
	bt [rsi + rbx], rdx	; [bitmap + rbx] = byte, al = bit
	jc found_duplicate
	
	; Set the bit in the bitmap
	bts [rsi + rbx], rdx

	inc rcx
	jmp check_dup_loop

found_duplicate:
	mov rax, 1
	ret
no_duplicates:
	mov rax, 0
	ret

section .note.GNU-stack