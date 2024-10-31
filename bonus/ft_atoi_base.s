;**************************************************************************** ;
;                                                                             ;
;                                                        :::      ::::::::    ;
;   ft_atoi_base.s                                     :+:      :+:    :+:    ;
;                                                    +:+ +:+         +:+      ;
;   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         ;
;                                                +#+#+#+#+#+   +#+            ;
;   Created: 2024/10/17 15:47:47 by tfregni           #+#    #+#              ;
;   Updated: 2024/10/17 15:47:47 by tfregni          ###   ########.fr        ;
;                                                                             ;
;**************************************************************************** ;

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

%macro invalid_base 1
cmp byte %1, ' '
je .base_invalid
cmp byte %1, 9
je .base_invalid
cmp byte %1, 10
je .base_invalid
cmp byte %1, 11
je .base_invalid
cmp byte %1, 12
je .base_invalid
cmp byte %1, 13
je .base_invalid
cmp byte %1, '+'
je .base_invalid
cmp byte %1, '-'
je .base_invalid
%endmacro

ft_atoi_base:
	; Safety check
	cmp rdi, 0					; if !str
	je error
	cmp rsi, 0					; if !base
	je error					; return 0
	; Save arguments
	mov r10, rdi				; r10: str
	mov r11, rsi				; r11: base
	; ft_strlen
	mov rdi, rsi				; set arg for ft_strlen
	call ft_strlen				; rax: base_len
	mov r12, rax				; r12: base_len
	; Base validation
	cmp rax, 2					; if base_len < 2
	jl error
	call validate_base			; if !validate_base
	cmp rax, 1
	je error					; return error
	; Init
	mov rbx, -1					; init str counter
	mov rdi, r10				; rdi: str
.skip_spaces:
 	inc rbx	
 	call ft_isspace
 	cmp rax, 1
 	je .skip_spaces
	; init_sign_reg:
 	xor r8, r8					; init r8: sign register
.handle_sign:
 	call handle_sign_func
 	cmp rax, -1					; if not sign
 	je .init_return_value		; break
 	inc rbx
 	add r8, rax					; add 1 if -, 0 if + 
 	jmp .handle_sign
.init_return_value:
	xor rax, rax				
.loop_str:						; outer loop
	cmp byte [r10 + rbx], 0	
	je check_negative	
	mov rcx, -1					; init base counter
	mov r13b, [r10 + rbx]		; str[rbx]
.loop_base:							; inner loop
	inc rcx	
	cmp byte [r11, rcx], 0			; if !base[rcx]
	je .update_result				
	cmp byte [r11 + rcx], r13b		; or base[rcx] == str[rbx]
	je .update_result				; goto update result
	jmp .loop_base
.update_result:
	cmp rcx, r12				; if rcx (base_idx) >= base_len
	jge check_negative			; end of base -> check the sign to return
	mul r12						; base_idx * return_val
	add rax, rcx				; return_val += base_idx
	inc rbx						; rbx++
	jmp .loop_str
error:
	mov rax, 0
	ret
check_negative:
	test r8b, 0x1				; if r8 is even (r8b & 0x1)
	jz return					; return
	neg rax						; return_val = -return_val
	ret
return:
	ret

; int validate_base(char *base
; 	rdi		-> base
; 	returns ->	0 if no duplicates
;				1 if duplicates
validate_base:
	; init bitmap
	mov rcx, 32						; num of bytes
	lea rsi, [rel bitmap]			; move bitmap address to rsi
.init_bitmap_loop:
	mov byte [rsi + rcx], 0			; 
	loop .init_bitmap_loop
	
	xor rax, rax					; rax = 0
.check_dup_loop:			
	mov al, [rdi + rcx]				; load current char
	test al, al						; check if it reached the end
	jz .base_valid			
	invalid_base [rdi + rcx]
.continue_base_loop:
	movzx rbx, al					; zero extend	
	shr rbx, 3						; find byte index by dividing by 8
	and al, 7						; find bit inside the byte
	movzx rdx, al
	; Check bitmap
	bt [rsi + rbx], rdx				; [bitmap + rbx] = byte, al = bit
	jc .base_invalid
	
	; Set the bit in the bitmap
	bts [rsi + rbx], rdx

	inc rcx
	jmp .check_dup_loop
.base_invalid:
	mov rax, 1
	ret
.base_valid:
	mov rax, 0
	ret

; returns	->	0 not space
;				1 is space
ft_isspace:
	cmp byte [rdi + rbx], ' '
	je .space
	cmp byte [rdi + rbx], 9
	jle .not_space
	cmp byte [rdi + rbx], 13
	jge .not_space
.space:
	mov rax, 1
	ret
.not_space:
	mov rax, 0
	ret

; returns	-> -1 no sign
;			-> 0 is +
;			-> 1 is -
handle_sign_func:
	cmp byte [rdi + rbx], '+'
	je is_plus
	cmp	byte [rdi + rbx], '-'
	je is_minus
	mov rax, -1
	ret
is_plus:
	mov rax, 0
	ret
is_minus:
	mov rax, 1
	ret

section .note.GNU-stack