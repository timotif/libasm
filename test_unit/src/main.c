/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:56:28 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/10 23:21:50 by tfregni          ###   ########.fr       */
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
	very_long_string[size - 1] = '\0';
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
	random_string[size - 1] = '\0';
	for (size_t i = 0; i < size - 1; i++)
		random_string[i] = (char)(rand() % 255 + 1);
	return (random_string);
}

char *create_random_printable_string(size_t size)
{
	char *random_string = malloc(size);
	if (!random_string)
	{
		printf("Memory allocation failed\n");
		exit (1);
	}
	random_string[size - 1] = '\0';
	for (size_t i = 0; i < size - 1; i++)
		random_string[i] = (char)(rand() % 94 + 33);
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
	// printf("global_result: %d test_result: %d\n", global_result, !test_result);
	#endif
	if (global_result)
		return ;
	global_result = !test_result;
}

t_test	get_test_type(int ac, char **av)
{
	if (ac < 2)
		return (ALL);
	if (!strcmp(av[1], "strlen") || !strcmp(av[1], "ft_strlen"))
		return (STRLEN);
	if (!strcmp(av[1], "strcpy") || !strcmp(av[1], "ft_strcpy"))
		return (STRCPY);
	if (!strcmp(av[1], "strcmp") || !strcmp(av[1], "ft_strcmp"))
		return (STRCMP);
	if (!strcmp(av[1], "write") || !strcmp(av[1], "ft_write"))
		return (WRITE);
	if (!strcmp(av[1], "read") || !strcmp(av[1], "ft_read"))
		return (READ);
	if (!strcmp(av[1], "mandatory"))
		return (MANDATORY);
	if (!strcmp(av[1], "bonus"))
		return (BONUS);
	return (UNKNOWN);
}

int main(int ac, char **av)
{
	/* TODO Implement Usage message */
	t_test test = get_test_type(ac, av);
	t_test_function test_functions[TOT_FUNCTIONS] = {
		test_strlen,
		test_strcpy,
		test_strcmp,
		test_write,
		test_read,
	};
	
	switch (test)
	{
	case STRLEN:
		test_strlen();
		break;
	case STRCPY:
		test_strcpy();
		break;
	case STRCMP:
		test_strcmp();
		break;
	case WRITE:
		test_write();
		break;
	case READ:
		test_read();
		break;
	case MANDATORY:
		for (size_t i = 0; i < MANDATORY; i++)
			test_functions[i]();
		break;
	// case BONUS:
	// 	for (size_t i = MANDATORY + 1; i < BONUS; i++)
	// 		test_functions[i]();
	case ALL:
		for (size_t i = 0; i < TOT_FUNCTIONS; i++)
			test_functions[i]();
		break;
	default:
		printf(RED "Unknown test\n" RESET);
		exit (1);
	}
	printf(BLUE "\n********************************\n" RESET);
	printf(BLUE "Unit tests global result: " RESET);
	print_unit_test_result();
	printf(BLUE "********************************\n" RESET);
	return (global_result);
}