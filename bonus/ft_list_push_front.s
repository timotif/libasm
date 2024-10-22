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

%ifdef DARWIN
%define FT_LIST_PUSH_FRONT _ft_list_push_front
%define MALLOC _malloc
%define CALL_MALLOC call _malloc
%else
%define FT_LIST_PUSH_FRONT ft_list_push_front
%define MALLOC malloc
%define CALL_MALLOC call [rel malloc wrt ..got]	; call compliant with PIE
section .note.GNU-stack
%endif

section .text
	global FT_LIST_PUSH_FRONT
	extern MALLOC

FT_LIST_PUSH_FRONT:
	; safety check (I accept NULL as data)
	cmp rdi, 0
	je .return_err
	; Save arguments
	push rdi					; save args to stack
	push rsi			
	; prepare arg for malloc 
	mov rdi, 16
	CALL_MALLOC
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
