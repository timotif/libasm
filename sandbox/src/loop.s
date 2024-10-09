section .data
	list db 1, 2, 3, 4
section .text
	global _start

_start:
	mov eax, 0 ; index to keep track of the current element
	mov cl, 0 ; keep track of the sum

loop:
	mov bl, [list + eax] ; get the current element
	add cl, bl ; add the current element to the sum
	; add eax, 1 ; increment the index
	inc eax ; increment the index
	cmp eax, 4 ; check if we have reached the end of the list
	je end ; if we have, jump to the end
	jmp loop ; otherwise, continue looping

end:
	mov eax, 1
	mov ebx, 1
	int 80h