;**************************************************************************** ;
;                                                                             ;
;                                                        :::      ::::::::    ;
;   ft_strcpy.s                                        :+:      :+:    :+:    ;
;                                                    +:+ +:+         +:+      ;
;   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         ;
;                                                +#+#+#+#+#+   +#+            ;
;   Created: 2024/10/17 15:47:47 by tfregni           #+#    #+#              ;
;   Updated: 2024/10/17 15:47:47 by tfregni          ###   ########.fr        ;
;                                                                             ;
;**************************************************************************** ;

; char *strcpy(char *restrict dst, const char *restrict src);
;	dst		-> rdi
;	src		-> rsi

%ifdef DARWIN
%define FT_STRCPY _ft_strcpy
%define FT_STRLEN _ft_strlen
%else
%define FT_STRCPY ft_strcpy
%define FT_STRLEN ft_strlen
section .note.GNU-stack
%endif

section .text
	global FT_STRCPY
	extern FT_STRLEN

; First approach
; _ft_strcpy:
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
FT_STRCPY:
	mov rbx, rdi ; save away rdi
	mov rdi, rsi ; set source string as arg for strlen
	call FT_STRLEN
	mov rdi, rbx ; get back rdi original content
	mov rcx, rax ; set the counter for rep on the return value of strlen
	inc rcx ; include null terminator
	rep movsb ; move a byte from rsi to rdi rcx times
	mov rax, rbx ; set return value to the original dst value
	ret
