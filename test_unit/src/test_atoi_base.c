/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_atoi_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:42:03 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/13 01:14:16 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test_libasm.h>

static int ft_isspace(char c) {
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

static int validate_base(char *base) {
	int	bitmap[256] = {0};

	while (*base) {
		if (bitmap[(int)*base]) {
			#ifdef DEBUG
			printf("Error: Duplicate character in base\n");
			#endif
			return (1);
		}
		if (ft_isspace(*base) || *base == '+' || *base == '-') {
			#ifdef DEBUG
			printf("Error: Invalid character in base: %c\n", *base);
			#endif
			return (1);
		}
		bitmap[(int)*base] = 1;
		base++;
	}
	return (0);
}

int ft_atoi_base_c(char *str, char *base) {
	int	ret;
	int	base_len;
	int	i_base;
	int sign;

	if (!str || !base)
		return (0);
	base_len = strlen(base);
	if (base_len < 2 || validate_base(base))
		return (0);
	while (ft_isspace(*str))
		str++;
	sign = 1;
	while (*str == '+' || *str == '-') {
		if (*str == '-')
			sign *= -1;
		str++;
	}
	// Loop through string
	ret = 0;
	while (*str) {
		i_base = 0;
		while (base[i_base]) {
			if (*str == base[i_base])
				break ;
			i_base++;
		}
		// Char not in base
		if (i_base >= base_len)
			return (ret);
		// Update result
		ret = ret * base_len + i_base;
		str++;
	}
	return (ret * sign);
}

static void	test(char *str, char *base)
{
	static int	test_number = 1;
	int ret, ret_c, ret_asm;
	
	printf("Test %d: ", test_number);
	#ifdef PROFILE
	// double time_spent_std, time_spent_ft;
	// char *dst_std;
	// time_spent_std = time_test(strdup, &dst_std, src);
	// time_spent_ft = time_test(ft_atoi_base, &dst_ft, src);
	// printf(" - time: %f/%fms - ", time_spent_std, time_spent_ft);
	// free(dst_std);
	# else
	ret_c = ft_atoi_base_c(str, base);
	ret_asm = ft_atoi_base(str, base);
	#endif
	#ifdef DEBUG
	printf("\nc:\tinput: %s base: %s - return: %d\n", (str) ? str : "NULL", (base) ? base:"NULL", ret_c);
	printf("asm:\tinput: %s base: %s - return: %d\n", (str) ? str : "NULL", (base) ? base:"NULL", ret_asm);
	#endif
	ret = ret_c == ret_asm;
	printf("%s" RESET, (ret) ? GREEN "OK\n" : RED "KO\n");
	update_unit_test_result(ret);
	test_number++;
}

char *create_string_without_duplicates(int size)
{
	if (size > 256)
		size = 256;
	char bitmap[256] = {0};

	srand(time(NULL));
	char *string = malloc(size);
	// No error checking because NULL string is handled in the functions
	string[size - 1] = '\0';
	int i = 0;
	while (i < size - 1) {
		int c = (rand() % 94 + 33);;
		if (bitmap[c]) {
			continue ;
		}
		string[(unsigned char)i] = c;
		bitmap[c] = 1;
		i++;		
	}
	return (string);
}

void test_atoi_base()
{
	printf(MAGENTA "\n*********************************\n");
	printf(MAGENTA "*             BONUS             *\n");
	printf(MAGENTA "*********************************\n\n" RESET);
	printf(BLUE "*** FT_ATOI_BASE_C vs. FT_ATOI_BASE_ASM ***\n" RESET);
	#ifdef DEBUG
	printf("DEBUG MODE: ON\n");
	#endif
	// Base tests
	test("42", "0123456789");
	test("42", "0123456789abcdef");
	test("E2", "     0123456789ABCDEF");
	test("-42", "0123456789");
	test("-42", "0123456789abcdef");
	test("42", "0123456789abcdef");
	test("ab", "0123456789abcdef");
	test("9a", "0123456789a");
	test("42", "012345678");
	test("-42", "    -0123456789ABCDEF");
	test("42", "- 0123456789");
	test("42", "0123456789-");
	test(NULL, "01");
	test("42", NULL);
	test("fddghsjkfh", "dhuislf");
	test("634278", "");
	test("634278", "0");
	test("101067", "01");
	test("101067", "            +++++--++0");
	test("101067", "            +++++--++0hdfdjk");
	char *str, *base;
	str = create_random_printable_string(100);
	base = create_string_without_duplicates(32);
	test(str, base);
	free(str);
	free(base);
	// Extra tests
	print_unit_test_result();
}