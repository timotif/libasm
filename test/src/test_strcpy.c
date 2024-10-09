/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:20:58 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/09 01:03:14 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test_libasm.h>

static void	test(char *dst, const char *src)
{
	static int	test_number = 1;
	char	*ret1 = strcpy(dst, src);
	bzero(dst, strlen(src) + 1);
	char	*ret2 = ft_strcpy(dst, src);
	int ret;
	
	printf("Test %d: ", test_number);
	ret =  ret1 == ret2 && !strcmp(dst, src);
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
	const char *src = "Hello world";
	test(dst, src);
	print_unit_test_result();
}