/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:40:47 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/13 11:45:07 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_list.h>

void	ft_swap_node(t_list *a, t_list *b, t_list *previous)
{
	if (previous)
		previous->next = b;
	a->next = b->next;
	b->next = a;
}

int	ft_node_cmp_next(t_list *a, t_list **begin_list, \
t_list **previous, int (*cmp)())
{
	t_list	*tmp;

	if (!a->data || !(a->next)->data)
		return (0);
	if ((cmp)(a->data, (a->next)->data) > 0)
	{
		tmp = a->next;
		if (!*previous)
			*begin_list = a->next;
		ft_swap_node(a, a->next, *previous);
		*previous = tmp;
		return (1);
	}
	return (0);
}

/* Useless function just added to save lines for norminette */
int	init_loop(t_list **begin_list, t_list **list_ptr, \
t_list **previous, int *sorted)
{
	if (!begin_list || !*begin_list)
		return (0);
	*list_ptr = *begin_list;
	*previous = 0;
	*sorted = 1;
	return (1);
}

void	ft_list_sort_c(t_list **begin_list, int (*cmp)())
{
	t_list	*list_ptr;
	t_list	*previous;
	t_list	*tail;
	int		sorted;

	sorted = 0;
	tail = 0;
	while (!sorted)
	{
		if (!init_loop(begin_list, &list_ptr, &previous, &sorted))
			return ;
		while (list_ptr->next != tail)
		{
			if (ft_node_cmp_next(list_ptr, begin_list, &previous, cmp))
			{
				sorted = 0;
				continue ;
			}
			previous = list_ptr;
			list_ptr = list_ptr->next;
		}
		tail = list_ptr;
	}
}
