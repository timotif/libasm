extern printf
extern exit

section .data
	msg db "Hello, world!", 0
	fmt db "Output is: %s", 10, 0 ; 10 is ASCII for newline, 0 is null terminator

section .text
	global _start

; printf(fmt, msg)
; exit(code)

main:
	sub rsp, 8 ; align the stack
	mov rdi, fmt ; first argument
	mov rsi, msg ; second argument
	xor eax, eax ; clear eax to indicate that there are no floating-point arguments.
	call printf ; matching what we declared with extern printf
	add rsp, 16 ; restore the stack pointer
	mov rdi, 42 ; exit code
	call exit

_start:
	call main

section .note.GNU-stack