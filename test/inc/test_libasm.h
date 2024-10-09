/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_libasm.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:31:18 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/08 23:35:37 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_LIBASM_H
# define TEST_LIBASM_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <time.h>
# include <colors.h>

/*** GLOBAL VARIABLE ***/
extern int global_result;
/***********************/

// General
void	update_unit_test_result(const int test_result);
void	print_unit_test_result(void);
char	*create_very_long_string(size_t size);
char	*create_random_string(size_t size);

// Libasm
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *restrict dst, const char *restrict src);

// Test
void	test_strlen();
void	test_strcpy();

#endif