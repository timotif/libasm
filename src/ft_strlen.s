;**************************************************************************** ;
;                                                                             ;
;                                                        :::      ::::::::    ;
;   ft_strlen.s                                        :+:      :+:    :+:    ;
;                                                    +:+ +:+         +:+      ;
;   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         ;
;                                                +#+#+#+#+#+   +#+            ;
;   Created: 2024/10/17 15:47:47 by tfregni           #+#    #+#              ;
;   Updated: 2024/10/17 15:47:47 by tfregni          ###   ########.fr        ;
;                                                                             ;
;**************************************************************************** ;
; size_t strlen(const char *s)
; 	s	-> rdi

%ifdef DARWIN
%define FT_STRLEN _ft_strlen
%else
%define FT_STRLEN ft_strlen
section .note.GNU-stack
%endif

section .text
	global FT_STRLEN

; First approach
FT_STRLEN:
	xor rax, rax ; init counter

_loop:
	cmp BYTE [rdi + rax], 0 ; BYTE specifies the size of the operand being accessed
	je _return
	inc rax
	jmp _loop

_return:
	ret

; Alternative approach scanning: 37% slower on a INT_MAX-long string
; ft_strlen:
;     xor rax, rax        ; Clear rax (will be used as the counter)
;     xor rcx, rcx        ; Clear rcx (will be used as the length counter)
;     not rcx             ; Set rcx to -1 (0xFFFFFFFFFFFFFFFF)
;     xor al, al          ; Clear al (set to 0, the null terminator)
;     repnz scasb         ; Scan for null terminator
;     not rcx             ; Invert rcx to get the length
;     dec rcx             ; Adjust length to exclude the null terminator
;     mov rax, rcx        ; Move the length to rax (return value)
;     ret
