/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 16:12:18 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/13 11:42:51 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_list.h>

int	ft_list_size_c(t_list *begin_list)
{
	int	len;

	len = 0;
	while (begin_list)
	{
		len++;
		begin_list = begin_list->next;
	}
	return (len);
}
