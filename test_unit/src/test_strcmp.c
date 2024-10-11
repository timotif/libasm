/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:32:03 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/11 12:39:19 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test_libasm.h>

#ifdef PROFILE
static double time_test(int *ret, int (*f)(const char *,const char *), const char *s1, const char *s2)
{
	clock_t start, end;
	double time_spent;
	
	start = clock();
	*ret = f(s1, s2);
	end = clock();
	time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
	return (time_spent);
}
#endif

static int normalize(int result)
{
    if (result < 0) return -1;
    if (result > 0) return 1;
    return 0;
}

static void	test(const char *s1, const char *s2)
{
	static int	test_number = 1;
	int ret;
	
	printf("Test %d: ", test_number);
	int ret1, ret2;
	#ifdef PROFILE
	double time_spent_std, time_spent_ft;
	time_spent_std = time_test(&ret1, strcmp, s1, s2);
	time_spent_ft = time_test(&ret2, ft_strcmp, s1, s2);
	printf(" - time: %f/%fms - ", time_spent_std, time_spent_ft);
	# else
	ret1 = strcmp(s1, s2);
	ret2 = ft_strcmp(s1, s2);
	#endif
	#ifdef DEBUG
	printf("\nstrcmp\t\ts1: %.1000s s2: %.1000s -> %d\n", s1, s2, strcmp(s1, s2));
	printf("ft_strcmp\ts1: %.1000s s2: %.1000s -> %d\n", s1, s2, ft_strcmp(s1, s2));
	#endif
	ret = normalize(ret1) == normalize(ret2); // normalize because with valgrind strcmp returns -1, 0, 1 
	printf("%s" RESET, (ret) ? GREEN "OK\n" : RED "KO\n");
	update_unit_test_result(ret);
	test_number++;
}

void test_strcmp()
{
	printf(BLUE "*** STRCMP vs. FT_STRCMP ***\n" RESET);
	#ifdef DEBUG
	printf("DEBUG MODE: ON\n");
	#endif
	// Base tests
	test("Hello world", "Hello world");
	test("Hello world", "Hello world!");
	test("Hello world!", "Hello world");
	test("", "");
	test("Hello world", "");
	test("", "Hello world");
	test("42", "43");
	test("43", "42");
	// Extra tests
	char *very_long_string = create_very_long_string(4096);
	char copy_very_long_string[4096];
	ft_strcpy(copy_very_long_string, very_long_string);
	copy_very_long_string[4094] = 'a';
	test(very_long_string, copy_very_long_string);
	free(very_long_string);
	print_unit_test_result();
}