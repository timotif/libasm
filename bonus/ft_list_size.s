;**************************************************************************** ;
;                                                                             ;
;                                                        :::      ::::::::    ;
;   ft_list_size.s                                     :+:      :+:    :+:    ;
;                                                    +:+ +:+         +:+      ;
;   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         ;
;                                                +#+#+#+#+#+   +#+            ;
;   Created: 2024/10/17 15:47:47 by tfregni           #+#    #+#              ;
;   Updated: 2024/10/17 15:47:47 by tfregni          ###   ########.fr        ;
;                                                                             ;
;**************************************************************************** ;

; typedef struct s_list
; {
; 	void *data;
; 	struct s_list *next;
; }
;	sizeof(void*)	= 8
;	sizeof(t_list*)	= 8
;	sizeof(t_list)	= 16

; int	ft_list_size(t_list *begin_list)
;	begin_list	-> rdi

section .text
	global ft_list_size

ft_list_size:
	xor rax, rax		; rax = 0
.loop:
	cmp rdi, 0			; if !begin_list; return
	je .return
	mov rdi, [rdi + 8]	; begin_list = begin_list->next
	inc rax				; rax++
	jmp .loop
.return:
	ret

section .note.GNU-stack