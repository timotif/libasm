/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:40:47 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/22 09:50:37 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_list.h>
#include <test_libasm.h>

void	ft_list_sort_c(t_list **begin_list, int (*cmp)(void *, void *)) {
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
			void *data = cur->data;
			void *data_next = cur->next->data;
			if (!data || !data_next)
				return ;
			int ret_cmp = cmp(data, data_next);
			if (ret_cmp > 0) {
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