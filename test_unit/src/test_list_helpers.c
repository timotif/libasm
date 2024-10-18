/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:31:13 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/18 17:09:37 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test_libasm.h>

/**
 * @brief: Deletes a list
 * @param: l: The list to delete
 * @param: expects 1 if the data was malloced, 0 otherwise
 */
void ft_list_delete(t_list **l, int malloced_data)
{
	t_list *tmp;

	while (*l) {
		tmp = *l;
		if (malloced_data)
			free(tmp->data);
		*l = (*l)->next;
		free(tmp);
	}
}

/**
 * @brief: Compares two lists
 * @param: l1: The first list
 * @param: l2: The second list
 * @param: cmp: The comparison function
 * @note: The comparison function will be called as cmp(l1->data, l2->data)
 * @return: 0 if the lists are equal, 1 otherwise
 */
int ft_list_cmp(t_list *l1, t_list *l2, int (*cmp)(void *, void *)) {
	while (l1 && l2) {
		if (l1->data == NULL || l2->data == NULL) {
			if (l1->data != l2->data)
				return (1);
			l1 = l1->next;
			l2 = l2->next;
			continue;
		} 
		if (cmp(l1->data, l2->data)) 
			return (1);
		l1 = l1->next;
		l2 = l2->next;
	}
  	if (l1 || l2) 
  		return (1);
  	return (0);
}

/**
 * @brief: Creates a list of random strings
 * @param: size: The size of the list
 * @return: The list
 */
t_list *create_list(size_t size) {
	t_list *begin;
	t_list *cur;
	size_t str_size;

	for (size_t i = 0; i < size; i++) {
		str_size = rand() % 25 + 1;
		t_list *new = ft_create_elem(create_random_printable_string(str_size));
		if (i == 0) {
			begin = new;
			cur = begin;
		} else {
			cur->next = new;
			cur = new;
		}
	}
	return (begin);
}

/**
 * @brief: Duplicates a list
 * @note: The data is duplicated (new allocated memory)
 */
t_list *ft_list_dup(t_list *list) {
	t_list *new = NULL;
	t_list *cur = NULL;

	while (list) {
		if (!new) {
			new = ft_create_elem(strdup(list->data));
			cur = new;
		} else {
			t_list *tmp = ft_create_elem(strdup(list->data));
			cur->next = tmp;
			cur = tmp;
		}
		list = list->next;
	}
	return (new);
}

#ifdef DEBUG
/**
 * @brief: Prints a list
 * @param: list: The list to print
 */
void print_list(t_list *list) {
	while (list) {
		printf("%s -> ", (list->data) ? (char *)list->data : "NULL");
		list = list->next;
	}
	printf("*END OF LIST*\n");
}
#endif