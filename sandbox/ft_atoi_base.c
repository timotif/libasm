#include <string.h>
#include <stdio.h>

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
			printf("Error: Invalid character in base\n");
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