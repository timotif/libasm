;**************************************************************************** ;
;                                                                             ;
;                                                        :::      ::::::::    ;
;   ft_strdup.s                                        :+:      :+:    :+:    ;
;                                                    +:+ +:+         +:+      ;
;   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         ;
;                                                +#+#+#+#+#+   +#+            ;
;   Created: 2024/10/17 15:47:47 by tfregni           #+#    #+#              ;
;   Updated: 2024/10/17 15:47:47 by tfregni          ###   ########.fr        ;
;                                                                             ;
;**************************************************************************** ;

; char *strdup(const char *s)
;	s	-> rdi

%ifdef DARWIN
%define FT_STRDUP _ft_strdup
%define FT_STRLEN _ft_strlen
%define ERRNO_LOCATION ___error
%define MALLOC _malloc
%define FT_STRCPY _ft_strcpy
%define CALL_MALLOC call _malloc
%define CALL_ERRNO call___error
%else
%define FT_STRDUP ft_strdup
%define FT_STRLEN ft_strlen
%define ERRNO_LOCATION __errno_location
%define MALLOC malloc
%define FT_STRCPY ft_strcpy
%define CALL_MALLOC call [rel malloc wrt ..got]
%define CALL_ERRNO call [rel __errno_location wrt ..got]
section .note.GNU-stack
%endif

section .text
	global FT_STRDUP
	extern FT_STRLEN
	extern ERRNO_LOCATION
	extern MALLOC
	extern FT_STRCPY

FT_STRDUP:
	push rdi ; save the src string to the stack
	call FT_STRLEN
	mov rdi, rax ; rdi: len(src)
	inc rdi ; add space for null-terminator
	CALL_MALLOC
	; xor rax, rax ; simulate failed call
	test rax, rax
	jz _errno
	mov rdi, rax
	pop rsi
	call FT_STRCPY
	ret

_errno:
	mov rdi, rax ; save error code
	neg rdi
	CALL_ERRNO
	mov [rax], rdi
	mov rax, 0
	ret
	