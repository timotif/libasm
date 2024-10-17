/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:37:10 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/17 13:37:51 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test_libasm.h>

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