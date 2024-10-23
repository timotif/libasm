/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:27:51 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/23 09:20:37 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_list.h>

void	ft_list_remove_if_c(t_list **begin_list, void *data_ref, \
							int (*cmp)(), void (*free_fct)(void *))
{
	t_list *cur;
	t_list *prev;

	if (!begin_list || !*begin_list || !cmp)
		return ;
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
			(free_fct)(cur->data);
			free(cur);
			if (!(*begin_list)) // List is empty
				return ;
			cur = prev->next;
			continue ;
		}
		prev = cur;
		cur = cur->next;
	}
}
