;**************************************************************************** ;
;                                                                             ;
;                                                        :::      ::::::::    ;
;   ft_write.s                                         :+:      :+:    :+:    ;
;                                                    +:+ +:+         +:+      ;
;   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         ;
;                                                +#+#+#+#+#+   +#+            ;
;   Created: 2024/10/17 15:47:47 by tfregni           #+#    #+#              ;
;   Updated: 2024/10/17 15:47:47 by tfregni          ###   ########.fr        ;
;                                                                             ;
;**************************************************************************** ;

; ssize_t write(int fd, const void buf[.count], size_t count)
;	fd				-> rdi
;	buff			-> rsi
;	count			-> rdx
;	syscall write	-> 1 (Linux) 0x2000004 (Darwin)

section .text
	global _ft_write
	%ifdef DARWIN
	extern ___error
	%else
	extern __errno_location
	%endif

_ft_write:
	%ifdef DARWIN
	mov rax, 0x2000004
	%else
	mov rax, 1
	%endif
	syscall
	; test rax, rax
	jc _errno
	ret
_errno:
	mov rdi, rax
	%ifndef DARWIN
	neg rdi
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
