/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_libasm.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:31:18 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/14 12:57:23 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_LIBASM_H
# define TEST_LIBASM_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <fcntl.h>
# include <limits.h>
# include <time.h>
# include <colors.h>
# include <ft_list.h>

/*** GLOBAL VARIABLE ***/
extern int global_result;
extern char *g_base_test_strings[];
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
	STRCMP,
	WRITE,
	READ,
	STRDUP,
	// Boundary
	MANDATORY,
	// Bonus functions
	ATOI_BASE,
	LIST,
	// Boundary
	BONUS,
	ALL,
	UNKNOWN,
} t_test;

// /* Bonus: list handling */
// typedef struct s_list
// {
// 	void			*data;
// 	struct s_list	*next;
// }	t_list;

/* function pointer typedef to make arrays of functions */
typedef void (*t_test_function)(void);

/* The total number of function is ALL-2 to account for MANDATORY and BONUS cases */
# define TOT_FUNCTIONS ALL - 2
/* Sleep time for better visual in testing */
# define SLEEP_TIME 1000000 * 0.2

// General
void	update_unit_test_result(const int test_result);
void	print_unit_test_result(void);
char	*create_very_long_string(size_t size);
char	*create_random_string(size_t size);
char	*create_random_printable_string(size_t size);

// Libasm
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *restrict dst, const char *restrict src);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t	ft_write(int fd, const void *buf, size_t count);
ssize_t	ft_read(int fd, void *buf, size_t count);
char	*ft_strdup(const char *s);
// Bonus
int		ft_atoi_base(char *str, char *base);
void	ft_list_push_front(t_list **begin_list, void *data);
int		ft_list_size(t_list *begin_list);
void	ft_list_sort(t_list **begin_list, int (*cmp)());
void	ft_list_remove_if(t_list **begin_list, void *data_ref, \
		int (*cmp)(), void (*free_fct)(void *));

// Test
void	test_strlen();
void	test_strcpy();
void	test_strcmp();
void	test_write();
void	test_read();
void	test_strdup();
// Bonus test
void	test_atoi_base();
void	test_list();

#endif