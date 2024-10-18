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
;	syscall write	-> 1

section .text
	global ft_write
	extern __errno_location

ft_write:
	mov rax, 1
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
	call __errno_location
	%endif
	mov [rax], rdi
	mov rax, -1
	ret

%ifndef DARWIN
section .note.GNU-stack
%endif
