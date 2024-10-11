; ssize_t write(int fd, const void buf[.count], size_t count);
section .text
	global ft_write
	extern __errno_location
; syscall write: 1
; args: rdi: fd
;		rsi: buff
;		rdx: count
ft_write:
	mov rax, 1
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