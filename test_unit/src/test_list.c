#include <test_libasm.h>

int ft_list_cmp(t_list *l1, t_list *l2, int (*cmp)()) {
	while (l1 && l2) {
		if (l1->data == NULL || l2->data == NULL) {
			if (l1->data != l2->data)
				return (1);
			l1 = l1->next;
			l2 = l2->next;
			continue;
		} 
		if (cmp(l1->data, l2->data, sizeof(void *))) return (1);
			l1 = l1->next;
			l2 = l2->next;
		}
  	if (l1 || l2) 
  		return (1);
  	return (0);
}

static t_list *create_list(size_t size) {
	t_list *begin;
	t_list *cur;

	for (size_t i = 0; i < size; i++) {
		if (i == 0) {
			begin = ft_create_elem(create_random_printable_string(10));
			cur = begin;
			continue ;
		}
		t_list *new = ft_create_elem(create_random_printable_string(10));
		cur->next = new;
		cur = new;
	}
	return (begin);
}

static t_list *ft_list_copy(t_list *list) {
	t_list *new = NULL;
	t_list *cur = NULL;

	while (list) {
		if (!new) {
			new = ft_create_elem(list->data);
			cur = new;
		} else {
			t_list *tmp = ft_create_elem(list->data);
			cur->next = tmp;
			cur = tmp;
		}
		list = list->next;
	}
	return (new);
}

#ifdef DEBUG
static void print_list(t_list *list) {
	while (list) {
		printf("%s -> ", (list->data) ? (char *)list->data : "NULL");
		list = list->next;
	}
	printf("\n");
}
#endif

static void test(t_list *list_c, t_list *list_asm) {
	int ret;
	static int test_number = 1;

	printf("Test %d: ", test_number);
	ret = !ft_list_cmp(list_c, list_asm, memcmp) && (ft_list_size_c(list_c) == ft_list_size(list_asm));
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

static void ft_list_delete(t_list **l)
{
	t_list *tmp;

	while (*l) {
		tmp = *l;
		*l = (*l)->next;
		free(tmp);
	}
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
	ft_list_delete(&list_c);
	ft_list_delete(&list_asm);
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
	ft_list_delete(&list_c);
	ft_list_delete(&list_asm);
	// TEST Create randomized list
	list_c = create_list(3);
	list_asm = ft_list_copy(list_c);
	test(list_c, list_asm);
	// TEST Sorting the list
	ft_list_sort(&list_asm, memcmp);
	ft_list_sort_c(&list_c, memcmp);
	test(list_c, list_asm);
	// Extra tests
	// Clean up
	ft_list_delete(&list_c);
	ft_list_delete(&list_asm);
	print_unit_test_result();
}
