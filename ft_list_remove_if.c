#include <test_libasm.h>

void	ft_list_remove_if_c(t_list **begin_list, void *data_ref, \
							int (*cmp)(), void (*free_fct)(void *))
{
	t_list *cur;
	t_list *prev;

	cur = *begin_list;
	prev = cur;
	while (cur)
	{
		if (!(*cmp)(cur->data, data_ref))
		{
			if (cur == prev) {
				*begin_list = cur->next;
				prev = *begin_list;
			}
			else 
				prev->next = cur->next;
			(*free_fct)(cur->data);
			free(cur);
			cur = prev->next;
		}
		prev = cur;
		cur = cur->next;
	}
}