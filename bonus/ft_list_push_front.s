;**************************************************************************** ;
;                                                                             ;
;                                                        :::      ::::::::    ;
;   ft_list_push_front.s                               :+:      :+:    :+:    ;
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

; void ft_list_push_front(t_list **begin_list, void *data)
;	**begin_lst	->	rdi
;	*data		->	rsi

section .text
	global ft_list_push_front
	extern malloc

ft_list_push_front:
	; safety check (I accept NULL as data)
	cmp rdi, 0
	je .return_err
	; Save arguments
	push rdi					; save args to stack
	push rsi			
	; prepare arg for malloc 
	mov rdi, 16
	call [rel malloc wrt ..got]	; call compliant with PIE
	cmp rax, 0					; if malloc returns NULL
	je .return_err				; return error
	; rax = new_node		
	pop rsi						; pop back (in reverse order)
	pop rdi		
	mov [rax], rsi				; new_node->data = data
	mov rdx, [rdi]				; rdx = *begin_lst
	mov [rax + 8], rdx			; new_node->next = *begin_lst
	mov [rdi], rax
.return:
	ret
.return_err:
	mov rax, 0
	ret

section .note.GNU-stack