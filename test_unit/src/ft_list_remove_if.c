/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:27:51 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/14 12:56:25 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_list.h>

/* The condition list_ptr == previous should be true only in the
first element of the list so it's my check for that condition */
void	ft_list_remove_if_c(t_list **begin_list, void *data_ref, \
int (*cmp)(), void (*free_fct)(void *))
{
	t_list	*list_ptr;
	t_list	*previous;

	if (!begin_list || !data_ref)
		return ;
	list_ptr = *begin_list;
	previous = list_ptr;
	while (list_ptr)
	{
		if (!(*cmp)(list_ptr->data, data_ref))
		{
			if (list_ptr == previous)
				*begin_list = list_ptr->next;
			else
				previous->next = list_ptr->next;
			(*free_fct)(list_ptr->data);
			previous = list_ptr;
			free(previous);
		}
		else
			previous = list_ptr;
		list_ptr = list_ptr->next;
	}
}
