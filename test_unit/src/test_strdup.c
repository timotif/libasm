/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:20:58 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/11 15:28:59 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test_libasm.h>

#ifdef PROFILE
static double time_test(char * (*f)(const char *), char **dst, const char *src)
{
	clock_t start, end;
	double time_spent;
	
	start = clock();
	*dst = f(src);
	end = clock();
	time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
	return (time_spent);
}
#endif

static void	test(const char *src)
{
	static int	test_number = 1;
	int ret;
	char *dst_ft;
	
	printf("Test %d: ", test_number);
	#ifdef PROFILE
	double time_spent_std, time_spent_ft;
	char *dst_std;
	time_spent_std = time_test(strdup, &dst_std, src);
	time_spent_ft = time_test(ft_strdup, &dst_ft, src);
	printf(" - time: %f/%fms - ", time_spent_std, time_spent_ft);
	free(dst_std);
	# else
	dst_ft = ft_strdup(src);
	#endif
	if (!dst_ft)
	{
		printf(RED "Malloc failed\n" RESET);
		test_number++;
		return ;
	}
	#ifdef DEBUG
	printf("Input: %.1000s - Output: %.1000s\n", (src) ? src: "NULL", (dst_ft) ? dst_ft : "NULL");
	#endif
	ret = !strcmp(dst_ft, src);
	printf("%s" RESET, (ret) ? GREEN "OK\n" : RED "KO\n");
	update_unit_test_result(ret);
	test_number++;
	free(dst_ft);
}

void	test_strdup()
{
	int max_len = 4096000;
	char *src;
	
	printf(BLUE "*** STRDUP vs. FT_STRDUP ***\n" RESET);
	#ifdef DEBUG
	printf("DEBUG MODE: ON\n");
	#endif
	// Base tests
	for (int i = 0; g_base_test_strings[i]; i++)
		test(g_base_test_strings[i]);
	// Extra tests
	src = create_very_long_string(max_len);
	test(src);
	free(src);
	src = create_random_string(max_len);
	test(src);
	free(src);
	print_unit_test_result();
}