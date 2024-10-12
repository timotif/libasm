; int ft_find_duplicates(char *base)
; 	rdi		->	base
; 	returns ->	0 if no duplicates
;				1 if duplicates
section .bss
	bitmap resb 32 ; 256-bit bitmap (32 bytes)
section .text
	global ft_find_duplicates
ft_find_duplicates:
	; init bitmap
	mov rcx, 32				; num of bytes
	lea rsi, [rel bitmap]		; move bitmap address to rsi
	xor rax, rax			; rax = 0
	rep stosb				; repeat storing al into [rdi] rcx times
	; rdi = base since before
	xor rcx, rcx			; init counter
check_dup_loop:	
	mov al, [rdi + rcx]		; load current char
	test al, al				; check if it reached the end
	jz no_duplicates	
	movzx rbx, al			; zero extend	
	shr rbx, 3				; find byte index by dividing by 8
	and al, 7				; find bit inside the byte
	movzx rdx, al
	; Check bitmap
	bt [rsi + rbx], rdx	; [bitmap + rbx] = byte, al = bit
	jc found_duplicate
	
	; Set the bit in the bitmap
	bts [rsi + rbx], rdx

	inc rcx
	jmp check_dup_loop

found_duplicate:
	mov rax, 1
	ret
no_duplicates:
	mov rax, 0
	ret

section .note.GNU-stack