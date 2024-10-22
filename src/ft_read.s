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

%ifdef DARWIN
%define FT_READ _ft_read
%define SYSCALL_READ 0x2000003
%define ERRNO_LOCATION ___error
%define CALL_ERRNO call ERRNO_LOCATION
%else
%define FT_READ ft_read
%define SYSCALL_READ 0
%define ERRNO_LOCATION __errno_location
%define CALL_ERRNO call [rel ERRNO_LOCATION wrt ..got]
section .note.GNU-stack
%endif

section .text
	global FT_READ
	extern ERRNO_LOCATION

FT_READ:
	mov rax, SYSCALL_READ
	syscall
	; test rax, rax
	jc _errno
	ret
_errno:
	mov rdi, rax
	%ifndef DARWIN
	neg rdi
	%endif
	CALL_ERRNO
	mov [rax], rdi
	mov rax, -1
	ret
