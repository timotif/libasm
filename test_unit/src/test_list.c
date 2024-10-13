#include <test_libasm.h>

int ft_list_cmp(t_list *l1, t_list *l2, int (*cmp)(const void *, const void *, size_t)) {
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

static void test(t_list *list_c, t_list *list_asm) {
	int ret;
	static int test_number = 1;

	printf("Test %d: ", test_number);
	ret = !ft_list_cmp(list_c, list_asm, memcmp);
	#ifdef DEBUG
	printf("\nc:\t%s\n", (list_c->data) ? (char *)list_c->data : "NULL");
	printf("asm:\t%s\n", (list_asm->data) ? (char *)list_asm->data : "NULL");
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
	t_list *list_c = ft_create_elem("Hello");
	t_list *list_asm = ft_create_elem("Hello");
	test(list_c, list_asm);
	ft_list_push_front_c(&list_c, "World");
	ft_list_push_front(&list_asm, "World");
	test(list_c, list_asm);		
	ft_list_delete(&list_c);
	ft_list_delete(&list_asm);
	list_c = ft_create_elem(NULL);
	list_asm = ft_create_elem(NULL);
	ft_list_push_front_c(&list_c, "World");
	ft_list_push_front(&list_asm, "World");
	test(list_c, list_asm);
	// Extra tests
	// Clean up
	ft_list_delete(&list_c);
	ft_list_delete(&list_asm);
	print_unit_test_result();
}
