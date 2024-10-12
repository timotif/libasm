; ssize_t read(int fd, void buf[.count], size_t count)
;	fd				-> rdi
;	buff			-> rsi
;	count			-> rdx
;	syscall read	-> 0

section .text
	global ft_read
	extern __errno_location

ft_read:
	mov rax, 0
	syscall
	test rax, rax
	js _errno
	ret
_errno:
	mov rdi, rax
	neg rdi
	call [rel __errno_location wrt ..got]	; call the function __errno_location in relative position
											; with respect to (wrt) the Global Offset Table (got)
											; this guarantees PIE compliance (Position Independent Executable)
	mov [rax], rdi
	mov rax, -1
	ret

section .note.GNU-stack