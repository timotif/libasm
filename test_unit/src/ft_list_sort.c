/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:40:47 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/14 00:08:39 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_list.h>

void	ft_list_sort_c(t_list **begin_list, int (*cmp)()) {
	t_list *cur;
	void *tmp;
	int sorted;

	if (!begin_list || !*begin_list || !cmp)
		return ;
	sorted = 0;
	while (!sorted) {
		sorted = 1;
		cur = *begin_list;
		while (cur->next) {
			if (cmp(cur->data, cur->next->data) > 0) {
				tmp = cur->data;
				cur->data = cur->next->data;
				cur->next->data = tmp;
				sorted = 0;
				break ;
			}
			cur = cur->next;
		}
	}
}