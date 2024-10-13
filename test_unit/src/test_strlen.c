/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:48:13 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/13 11:01:52 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test_libasm.h>

#ifdef PROFILE
static double time_test(size_t *ret, size_t (*f)(const char *), const char *s)
{
	clock_t start, end;
	double time_spent;
	
	start = clock();
	*ret = f(s);
	end = clock();
	time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
	return (time_spent);
}
#endif

static void	test(const char *s)
{
	static int	test_number = 1;
	int	ret;
	size_t len_std, len_ft;
	
	printf("Test %d: ", test_number);
	#ifdef PROFILE
	double time_spent_std, time_spent_ft;
	time_spent_std = time_test(&len_std, strlen, s);
	time_spent_ft = time_test(&len_ft, ft_strlen, s);
	printf(" - time: %f/%fms - ", time_spent_std, time_spent_ft);
	# else
	len_std = strlen(s);
	len_ft = ft_strlen(s);
	#endif
	// #if defined(DEBUG) || defined(PROFILE)
	ret = (len_std == len_ft);
	#ifdef DEBUG
	printf("%.1000s: %ld - %ld -> ret: %d\n", s, len_std, len_ft, ret);
	#endif
	#ifndef NOSLEEP
	usleep(SLEEP_TIME);
	#endif
	printf("%s" RESET, (ret) ? GREEN "OK\n" : RED "KO\n");
	update_unit_test_result(ret);
	test_number++;
}

void	test_strlen()
{
	printf(MAGENTA "*********************************\n");
	printf(MAGENTA "*           MANDATORY           *\n");
	printf(MAGENTA "*********************************\n\n" RESET);
	printf(BLUE "*** STRLEN vs. FT_STRLEN ***\n" RESET);
	#ifdef DEBUG
	printf("DEBUG MODE: ON\n");
	#endif
	// Base tests
	for (int i = 0; g_base_test_strings[i]; i++)
		test(g_base_test_strings[i]);
	// Extra tests
	char *very_long_string = create_very_long_string((size_t)INT_MAX + 100);
	test(very_long_string); // String longer than INT_MAX
	free(very_long_string);
	char *random_string = create_random_string(1000);
	test(random_string); // Random string
	free(random_string);
	print_unit_test_result();
}