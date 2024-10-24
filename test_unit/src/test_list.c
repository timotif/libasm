/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:32:27 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/23 09:42:23 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test_libasm.h>

static void test(t_list *list_c, t_list *list_asm) {
	int ret;
	static int test_number = 1;

	printf("Test %d: ", test_number);
	ret = !ft_list_cmp(list_c, list_asm, strcmp);
	ret = ret && (ft_list_size_c(list_c) == ft_list_size(list_asm));
	#ifdef DEBUG
	printf("\nc:\t");
	print_list(list_c);
	printf("asm:\t");
	print_list(list_asm);
	#endif
	#ifndef NOSLEEP
	usleep(SLEEP_TIME);
	#endif
	printf("%s" RESET, (ret) ? GREEN "OK\n" : RED "KO\n");
	update_unit_test_result(ret);
	test_number++;
}

void test_list() {
	printf(BLUE "*** FT_LIST_C vs. FT_LIST_ASM ***\n" RESET);
	#ifdef DEBUG
	printf("DEBUG MODE: ON\n");
	#endif
	// Base tests
	// TEST Create element
	t_list *list_c = ft_create_elem("Hello");
	t_list *list_asm = ft_create_elem("Hello");
	test(list_c, list_asm);
	// TEST Push front
	ft_list_push_front_c(&list_c, "World");
	ft_list_push_front(&list_asm, "World");
	test(list_c, list_asm);		
	ft_list_delete(&list_c, 0);
	ft_list_delete(&list_asm, 0);
	// TEST Creating element with NULL data
	list_c = ft_create_elem(NULL);
	list_asm = ft_create_elem(NULL);
	ft_list_push_front_c(&list_c, "World");
	ft_list_push_front(&list_asm, "World");
	ft_list_push_front_c(&list_c, "Hello");
	ft_list_push_front(&list_asm, "Hello");
	ft_list_push_front_c(&list_c, "Zizi");
	ft_list_push_front(&list_asm, "Zizi");
	test(list_c, list_asm);
	// TEST Push NULL element
	ft_list_push_front_c(&list_c, NULL);
	ft_list_push_front(&list_asm, NULL);
	test(list_c, list_asm);
	// TEST Sorting the list
	ft_list_sort_c(&list_c, memcmp);
	ft_list_sort(&list_asm, memcmp);
	test(list_c, list_asm);
	// TEST Adding an int to the list
	int list_int = 123;
	ft_list_push_front(&list_c, (void *)&list_int);
	ft_list_push_front(&list_asm, (void *)&list_int);
	test(list_c, list_asm);
	// TEST Sorting the list with an int
	ft_list_sort_c(&list_c, memcmp);
	ft_list_sort(&list_asm, memcmp);
	test(list_c, list_asm);
	// TEST Passing null parameters 
	ft_list_sort_c(NULL, memcmp);
	ft_list_sort(NULL, memcmp);
	test(list_c, list_asm);
	ft_list_sort_c(&list_c, NULL);
	ft_list_sort(&list_asm, NULL);
	test(list_c, list_asm);
	ft_list_delete(&list_c, 0);
	ft_list_delete(&list_asm, 0);
	// TEST Sorting a list with 1 element
	list_c = ft_create_elem("Hello");
	list_asm = ft_create_elem("Hello");
	ft_list_sort_c(&list_c, strcmp);
	ft_list_sort(&list_asm, strcmp);
	test(list_c, list_asm);
	ft_list_delete(&list_c, 0);
	// TEST Create randomized list
	list_c = create_list(10);
	list_asm = ft_list_dup(list_c);
	test(list_c, list_asm);
	// TEST Sorting the list
	ft_list_sort_c(&list_c, strcmp);
	ft_list_sort(&list_asm, strcmp);
	test(list_c, list_asm);
	ft_list_delete(&list_c, 1);
	ft_list_delete(&list_asm, 1);
	// TEST Removing an element
	list_c = ft_create_elem(strdup("0"));
	ft_list_push_front_c(&list_c, strdup("1"));
	ft_list_push_front_c(&list_c, strdup("2"));
	ft_list_push_front_c(&list_c, strdup("3"));
	list_asm = ft_list_dup(list_c);
	test(list_c, list_asm);
	ft_list_remove_if_c(&list_c, "1", strcmp, free);
	ft_list_remove_if(&list_asm, "1", strcmp, free);
	test(list_c, list_asm);
	// TEST Removing an element from the beginning
	ft_list_remove_if_c(&list_c, "3", strcmp, free);
	ft_list_remove_if(&list_asm, "3", strcmp, free);
	test(list_c, list_asm);
	// TEST Removing an element from the end
	ft_list_remove_if_c(&list_c, "0", strcmp, free);
	ft_list_remove_if(&list_asm, "0", strcmp, free);
	test(list_c, list_asm);
	// TEST Removing the last element
	ft_list_remove_if_c(&list_c, "2", strcmp, free);
	ft_list_remove_if(&list_asm, "2", strcmp, free);
	test(list_c, list_asm);
	// TEST Removing an element that doesn't exist
	ft_list_remove_if_c(&list_c, "2", strcmp, free);
	ft_list_remove_if(&list_asm, "2", strcmp, free);
	test(list_c, list_asm);
	// TEST Removing empty element
	ft_list_remove_if_c(&list_c, "", strcmp, free);
	ft_list_remove_if(&list_asm, "", strcmp, free);
	test(list_c, list_asm);
	// TEST Removing NULL element
	ft_list_remove_if_c(&list_c, NULL, ft_strcmp, free);
	ft_list_remove_if(&list_asm, NULL, ft_strcmp, free);
	test(list_c, list_asm);
	// TEST Removing from NULL list
	ft_list_remove_if_c(NULL, "2", strcmp, free);
	ft_list_remove_if(NULL, "2", strcmp, free);
	test(list_c, list_asm);
	// Extra tests
	// Clean up
	ft_list_delete(&list_c, 1);
	ft_list_delete(&list_asm, 1);
	print_unit_test_result();
}
