/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:07:32 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/13 11:41:36 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_create_elem(void *data)
{
	t_list	*new_node;

	new_node = NULL;
	new_node = malloc(sizeof(*new_node));
	if (new_node)
	{
		new_node->data = data;
		new_node->next = NULL;
	}
	return (new_node);
}
