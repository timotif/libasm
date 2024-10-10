; ssize_t write(int fd, const void buf[.count], size_t count);
section .text
	global ft_write
; syscall write: 4
; args: rdi: fd
;		rsi: buff
;		rdx: count
ft_write:
	mov rax, 1
	syscall
	ret

section .note.GNU-stack