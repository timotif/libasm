; ft_list_remove_if
; Allowed functions : free
; • Create the function ft_list_remove_if which removes from the list, all elements
; whose data compared to data_ref using cmp, makes cmp return 0.
; • The data from an element to be erased should be freed using free_fct
; • Here’s how it should be prototyped :
;	void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
; • Function pointed by cmp and by free_fct will be used as follows :
;	(*cmp)(list_ptr->data, data_re
;	(*free_fct)(list_ptr->data);

section .note.GNU-stack