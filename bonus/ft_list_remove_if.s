;**************************************************************************** ;
;                                                                             ;
;                                                        :::      ::::::::    ;
;   ft_list_remove_if.s                                :+:      :+:    :+:    ;
;                                                    +:+ +:+         +:+      ;
;   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+         ;
;                                                +#+#+#+#+#+   +#+            ;
;   Created: 2024/10/17 15:47:47 by tfregni           #+#    #+#              ;
;   Updated: 2024/10/17 15:47:47 by tfregni          ###   ########.fr        ;
;                                                                             ;
;**************************************************************************** ;

; Allowed functions : free
; • Create the function ft_list_remove_if which removes from the list, all elements
; whose data compared to data_ref using cmp, makes cmp return 0.
; • The data from an element to be erased should be freed using free_fct
; • Here’s how it should be prototyped :
;	void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
; • Function pointed by cmp and by free_fct will be used as follows :
;	(*cmp)(list_ptr->data, data_ref);
;	(*free_fct)(list_ptr->data);

; typedef struct s_list
; {
; 	void *data;
; 	struct s_list *next;
; }
;	sizeof(void*)	= 8
;	sizeof(t_list*)	= 8
;	sizeof(t_list)	= 16
;
;	void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
;		begin_list	->	rdi
;		data_ref	->	rsi
;		cmp			->	rdx
;		free_fct	->	rcx

section .text
	global _ft_list_remove_if
	extern free

%macro SAFETY_CHECK 0
	cmp rdi, 0
	je .return
	cmp rsi, 0
	je .return
	cmp rdx, 0
	je .return
	cmp rcx, 0
	je .return
	cmp qword [rdi], 0
	je .return
	cmp qword [rdx], 0
	je .return
	cmp qword [rcx], 0
	je .return
%endmacro

%macro PUSH_ARGS 0
push r8
push r9
push r10
push r11
push r12
%endmacro

%macro POP_ARGS 0
pop r12
pop r11
pop r10
pop r9
pop r8
%endmacro

_ft_list_remove_if:
	SAFETY_CHECK
							; r8 = cur
							; r9 = prev
	mov r10, rdx			; r10 = cmp
	mov r11, rcx			; r11 = free_fct
	mov r12, rdi			; r12 = begin_list
	mov r8, [r12]			; cur = *begin_list
	mov r9, r8				; prev = cur
.list_loop:	
	test r8, r8				; while (cur)
	jz .return	
	mov rdi, [r8]			; 
	PUSH_ARGS	
	call r10	
	POP_ARGS	
	cmp rax, 0				; if (*cmp)(cur->data, data_ref) == 0 
	je .remove				; goto remove
.next:	
	mov r9, r8				; prev = cur
	mov r8, [r8 + 8]		; cur = prev->next
	jmp .list_loop	
.remove:	
	cmp r8, r9	
	je .case_beginning		; if (cur == prev) goto .case_beginning
	.not_beginning:			; else
		mov rdx, [r8 + 8]	; prev->next = cur->next
		mov [r9 + 8], rdx
		jmp .free
	.case_beginning:
		mov rdx, [r8 + 8]
		mov [r12], rdx		; *begin_list = cur->next
		mov r9, [r12]				; prev = *begin_list
		jmp .free	
	.free:	
		mov rdi, [r8]	
		PUSH_ARGS	
		call r11			; (free_fct)(cur->data);
		POP_ARGS	
		PUSH_ARGS	
		mov rdi, r8			; free(cur)
		%ifndef DARWIN
		call [rel free wrt ..got]
		%else
		call free
		%endif
		POP_ARGS
	.case_end:
		mov rdx, [r12]
		test rdx, rdx
		jz .return
		mov r8, [r9 + 8]	; cur = prev->next
		jmp .list_loop
.return:
	mov rdi, r12			; put back **begin_list
	ret


%ifndef DARWIN
section .note.GNU-stackn
%endif
