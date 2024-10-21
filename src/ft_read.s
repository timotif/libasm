;**************************************************************************** ;
;                                                                             ;
;                                                        :::      ::::::::    ;
;   ft_read.s                                          :+:      :+:    :+:    ;
;                                                    +:+ +:+         +:+      ;
;   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         ;
;                                                +#+#+#+#+#+   +#+            ;
;   Created: 2024/10/17 15:47:47 by tfregni           #+#    #+#              ;
;   Updated: 2024/10/17 15:47:47 by tfregni          ###   ########.fr        ;
;                                                                             ;
;**************************************************************************** ;

; ssize_t read(int fd, void buf[.count], size_t count)
;	fd				-> rdi
;	buff			-> rsi
;	count			-> rdx
;	syscall read	-> 0

section .text
	global _ft_read
	%ifndef DARWIN
	extern __errno_location
	%else
	extern ___error
	%endif

_ft_read:
	mov rax, 0
	syscall
	test rax, rax
	js _errno
	ret
_errno:
	mov rdi, rax
	neg rdi
	%ifndef DARWIN
	call [rel __errno_location wrt ..got]	; call the function __errno_location in relative position
											; with respect to (wrt) the Global Offset Table (got)
											; this guarantees PIE compliance (Position Independent Executable)
	%else
	call ___error
	%endif
	mov [rax], rdi
	mov rax, -1
	ret

%ifndef DARWIN
section .note.GNU-stack
%endif
