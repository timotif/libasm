/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:56:28 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/17 15:24:35 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test_libasm.h>

int global_result = 0;
char *g_base_test_strings[] = {
	"Hello world",
	"42",
	"a", // Single charact
	"", // Empty string
	"!@#$%^&*()",  // Special chars
	"こんにちは",  // Multibyte
	"Hello\0World", // Null char in the middle
	"   Leading spaces", 
	"Trailing spaces   ", 
	"Line1\nLine2\nLine3",
	"Tab\tSeparated\tValues",
	NULL
};

void	print_unit_test_result(void)
{
	if (global_result)
		printf(RED "FAILED\n" RESET);
	else
		printf(GREEN "PASSED\n" RESET);
}

void	update_unit_test_result(const int test_result)
{
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
	if (!strcmp(av[1], "strdup") || !strcmp(av[1], "ft_strdup"))
		return (STRDUP);
	if (!strcmp(av[1], "mandatory"))
		return (MANDATORY);
	if (!strcmp(av[1], "atoi_base") || !strcmp(av[1], "ft_atoi_base"))
		return (ATOI_BASE);
	if (!strncmp(av[1], "list", 4) || !strncmp(av[1], "ft_list", 7))
		return (LIST);
	if (!strcmp(av[1], "bonus"))
		return (BONUS);
	return (UNKNOWN);
}

int main(int ac, char **av)
{
	t_test test = get_test_type(ac, av);
	t_test_function test_functions[TOT_FUNCTIONS] = {
		test_strlen,
		test_strcpy,
		test_strcmp,
		test_write,
		test_read,
		test_strdup,
		test_atoi_base,
		test_list
	};
	// Seed random
	srand(time(NULL));
	
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
	case STRDUP:
		test_strdup();
		break;
	case MANDATORY:
		for (size_t i = 0; i < MANDATORY; i++)
			test_functions[i]();
		break;
	case ATOI_BASE:
		test_atoi_base();
		break;
	case LIST:
		test_list();
		break;
	case BONUS:
		for (size_t i = MANDATORY; i < BONUS - 1; i++)
			test_functions[i]();
		break;
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