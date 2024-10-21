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

section .text
	global _ft_strdup
	extern _ft_strlen
	%ifdef DARWIN
	extern ___error
	%else
	extern __errno_location
	%endif
	extern _malloc
	extern _ft_strcpy

_ft_strdup:
	push rdi ; save the src string to the stack
	call _ft_strlen
	mov rdi, rax ; rdi: len(src)
	inc rdi ; add space for null-terminator
	%ifndef DARWIN
	call [rel malloc wrt ..got]
	%else
	call _malloc
	%endif
	; xor rax, rax ; simulate failed call
	test rax, rax
	jz _errno
	mov rdi, rax
	pop rsi
	call _ft_strcpy
	ret

_errno:
	mov rdi, rax ; save error code
	neg rdi
	%ifndef DARWIN
	call [rel __errno_location wrt ..got]
	%else
	call ___error
	%endif
	mov [rax], rdi
	mov rax, 0
	ret

%ifndef DARWIN
section .note.GNU-stack
%endif
