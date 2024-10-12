#include <stdio.h>

int ft_atoi_base(char *str, char *base);
int ft_atoi_base_c(char *str, char *base);

void test(char *str, char *base)
{
	int ret = ft_atoi_base(str, base);
	printf("asm:\t%d\n", ret);
	ret = ft_atoi_base_c(str, base);
	printf("c:\t%d\n", ret);
	printf("**************\n");
}

int main(int ac, char **av)
{
	if (ac == 3) {
		test(av[1], av[2]);
		return (0);
	}
	int ret = ft_atoi_base_c("42", "04");
	printf("%d\n", ret);
	test("-42", "0123456789abcdef");
	test("42", "0123456789abcdef");
	test("ab", "0123456789abcdef");
	test("9a", "0123456789a");
	test("42", "012345678");
	return (0);
}