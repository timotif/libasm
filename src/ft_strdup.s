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
	global ft_strdup
	extern ft_strlen
	extern __errno_location
	extern malloc
	extern ft_strcpy

ft_strdup:
	push rdi ; save the src string to the stack
	call ft_strlen
	mov rdi, rax ; rdi: len(src)
	inc rdi ; add space for null-terminator
	call [rel malloc wrt ..got]
	; xor rax, rax ; simulate failed call
	test rax, rax
	jz _errno
	mov rdi, rax
	pop rsi
	call ft_strcpy
	ret

_errno:
	mov rdi, rax ; save error code
	neg rdi
	call [rel __errno_location wrt ..got]
	mov [rax], rdi
	mov rax, 0
	ret

section .note.GNU-stack