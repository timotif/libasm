;**************************************************************************** ;
;                                                                             ;
;                                                        :::      ::::::::    ;
;   ft_list_sort.s                                     :+:      :+:    :+:    ;
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

; void	ft_list_sort_c(t_list **begin_list, int (*cmp)())
;	begin_list	-> rdi
;	cmp			-> rsi

%ifdef DARWIN
%define FT_LIST_SORT _ft_list_sort
%else 
%define FT_LIST_SORT ft_list_sort
section .note.GNU-stack
%endif

section .text
	global FT_LIST_SORT

%macro SAFETY_CHECK 0
	cmp rdi, 0
	je .return
	cmp rsi, 0
	je .return
	cmp qword [rdi], 0
	je .return
	cmp qword [rsi], 0
	je .return
%endmacro

%macro PUSH_ARGS 0
	push rcx
	push r10
	push r11
%endmacro

%macro POP_ARGS 0
	pop r11
	pop r10
	pop rcx
%endmacro

section .text
FT_LIST_SORT:
	SAFETY_CHECK
	xor r9, r9			; r9: sorted flag
	mov r10, rsi		; r10 = (*cmp)()
	mov r11, [rdi]		; r11 = *_begin_list
.unsorted_loop:			; outer loop
	cmp r9, 1			; if sorted
	je .return			; 	goto return
	mov r9, 1			; sorted = 1
	mov r12, r11		; cur = *begin_list
	mov rcx, [r12 + 8]	; rcx = cur->next
.list_loop:				; inner_loop
	cmp rcx, 0			; if !cur->next
	je .unsorted_loop	;	goto outer loop
	mov rdi, [r12]		;	rdi = cur->data
	mov rsi, [rcx]		;	rsi = cur->next->data
	; Avoiding to pass NULL to comparing function
	test rdi, rdi
	jz .next
	test rsi, rsi
	jz .next
	PUSH_ARGS			; 	save args
	call r10			; 	compare
	POP_ARGS			; 	pop args
	cdqe				; expands to 64-bit so that a 32-bit 
						; result is still interpreted correctly  
	test rax, rax		
	jle .next
.swap_data:
	mov r8, [r12]
	mov rbx, [rcx]
	mov [r12], rbx
	mov [rcx], r8
	xor r9, r9			; init sorted flag
	jmp .unsorted_loop	; goto outer loop
.next:
	mov r12, rcx		; cur = cur->next
	mov rcx, [r12 + 8]	; rcx = cur->next
	jmp .list_loop		; goto inner loop
.return:
	ret

%ifndef DARWIN
section .note.GNU-stackn
%endif
