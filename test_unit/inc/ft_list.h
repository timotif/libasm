/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:13:54 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/14 12:56:58 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H
# include <stdlib.h>

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

t_list	*ft_create_elem(void *data);
void	ft_list_push_front_c(t_list **begin_list, void *data);
int		ft_list_size_c(t_list *begin_list);
void	ft_list_sort_c(t_list **begin_list, int (*cmp)());
void	ft_list_remove_if_c(t_list **begin_list, void *data_ref, \
		int (*cmp)(), void (*free_fct)(void *));

#endif
