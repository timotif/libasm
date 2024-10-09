section .data
	msg db 'Hello World!', 0

section .text
	global _start	; Entry point for the program
					; global makes the label visible to the linker
					; _start is a label. Labels are used to mark locations in the code

_start:
	; Write the message to stdout
	mov rax, 1		; syscall number for sys_write
	mov rdi, 1		; file descriptor for stdout
	mov rsi, msg	; pointer to the message
	mov rdx, 13		; message length
	syscall

	; Exit the program
	mov rax, 60		; syscall number for sys_exit
	xor rdi, rdi	; exit code 0
	syscall
