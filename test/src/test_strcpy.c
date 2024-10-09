/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:20:58 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/09 12:32:10 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test_libasm.h>

#ifdef PROFILE
static double time_test(char * (*f)(char *restrict,const char *restrict), char *dst, const char *src)
{
	clock_t start, end;
	double time_spent;
	
	start = clock();
	dst = f(dst, src);
	end = clock();
	time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
	return (time_spent);
}
#endif

static void	test(char *dst, const char *src)
{
	static int	test_number = 1;
	int ret;
	char *dst_ft;
	
	printf("Test %d: ", test_number);
	#ifdef PROFILE
	double time_spent_std, time_spent_ft;
	time_spent_std = time_test(strcpy, dst, src);
	bzero(dst, strlen(dst));
	dst_ft = dst;
	time_spent_ft = time_test(ft_strcpy, dst_ft, src);
	printf(" - time: %f/%fms - ", time_spent_std, time_spent_ft);
	# else
	dst_ft = ft_strcpy(dst, src);
	#endif
	#ifdef DEBUG
	printf("Input: %.1000s - Output: %.1000s\n", src, dst_ft);
	printf("Expected return: %p - Returned: %p\n", dst, dst_ft);
	#endif
	ret = (dst_ft == dst) && !strcmp(dst_ft, src);
	printf("%s" RESET, (ret) ? GREEN "OK\n" : RED "KO\n");
	update_unit_test_result(ret);
	test_number++;
}

void	test_strcpy()
{
	printf(BLUE "*** STRCPY vs. FT_STRCPY ***\n" RESET);
	#ifdef DEBUG
	printf("DEBUG MODE: ON\n");
	#endif
	char dst[100];
	test(dst, "Hello world");
	test(dst, "42");
	test(dst, "a"); // Single character
	test(dst, ""); // Empty string
	test(dst, "                       "); // White spaces
	test(dst, "!@#$%^&*()");  // Special characters
    test(dst, "こんにちは");  // Multibyte characters
	print_unit_test_result();
}