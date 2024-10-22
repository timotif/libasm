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

%ifdef DARWIN
%define FT_WRITE ft_write
%define SYSCALL_WRITE 0x2000004
%define ERRNO_LOCATION ___error
%define CALL_ERRNO call ERRNO_LOCATION
%else 
%define FT_WRITE ft_write
%define SYSCALL_WRITE 1
%define ERRNO_LOCATION __errno_location
%define CALL_ERRNO call [rel ERRNO_LOCATION wrt ..got]
section .note.GNU-stack
%endif

section .text
	global FT_WRITE
	extern ERRNO_LOCATION

FT_WRITE:
	mov rax, SYSCALL_WRITE
	syscall
	%ifdef DARWIN
	jc _errno			; on Mac the syscall sets the carry flag and returns the error code
	%else
	test rax, rax		; on Linux the syscall returns the negative error code
	js _errno
	%endif
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
