; ssize_t read(int fd, void buf[.count], size_t count);
section .text
	global ft_read
; syscall read: 0
; args: rdi: fd
;		rsi: buff
;		rdx: count
ft_read:
	mov rax, 0
	syscall
	ret

section .note.GNU-stack