/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:56:28 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/08 23:35:22 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test_libasm.h>

int global_result = 0;

char *create_very_long_string(size_t size)
{
	char *very_long_string = malloc(size);
	if (!very_long_string)
	{
		printf("Memory allocation failed\n");
		exit (1);
	}
	very_long_string[size] = '\0';
	memset(very_long_string, '~', size - 1);
	return (very_long_string);
}

char *create_random_string(size_t size)
{
	char *random_string = malloc(size);
	if (!random_string)
	{
		printf("Memory allocation failed\n");
		exit (1);
	}
	random_string[size] = '\0';
	for (size_t i = 0; i < size - 1; i++)
		random_string[i] = (char)(rand() % 255 + 1);
	return (random_string);
}

void	print_unit_test_result(void)
{
	if (global_result)
		printf(RED "FAILED\n" RESET);
	else
		printf(GREEN "PASSED\n" RESET);
}

void	update_unit_test_result(const int test_result)
{
	#ifdef DEBUG
	printf("global_result: %d test_result: %d\n", global_result, test_result);
	#endif
	if (global_result)
		return ;
	global_result = !test_result;
}

int main(void)
{
	// test_strlen();
	test_strcpy();
}