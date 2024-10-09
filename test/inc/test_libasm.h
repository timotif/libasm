/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_libasm.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:31:18 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/09 11:38:57 by tfregni          ###   ########.fr       */
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

/**
 * Stack of tests 
 * The enum is organized like so:
 * - mandatory functions
 * - MANDATORY (acts like rsb register: sets a floor)
 * - mandatory functions are 0 <= function < MANDATORY
 * - bonus functions
 * - BONUS
 * - bonus functions are MANDATORY < function < BONUS
 * - ALL (the total number of functions is ALL - 2)
 */
typedef enum e_test {
	// Mandatory functions
	STRLEN,
	STRCPY,
	// Boundary
	MANDATORY,
	// Bonus functions
	// Boundary
	BONUS,
	ALL,
	UNKNOWN,
} t_test;

/* function pointer typedef to make arrays of functions */
typedef void (*t_test_function)(void);

/* The total number of function is ALL-2 to account for MANDATORY and BONUS cases */
# define TOT_FUNCTIONS ALL - 2

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