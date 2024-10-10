/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:42:45 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/11 00:11:51 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test_libasm.h>

static void	test(const void *buf, size_t count)
{
	static int	test_number = 1;
	int ret;
	int ret1, ret2;
	char *filename = ".test_read";
	
	printf("Test %d: ", test_number);
	int file_fd = open(filename, O_CREAT | O_WRONLY, 0644);
	if (file_fd < 0 || write(file_fd, buf, count) < 0)
	{
		printf(RED "File creation failed\n" RESET);
		test_number++;
		return ;
	}
	close(file_fd);
	
	// Init buffers
	char *buffer_std, *buffer_ft;
	buffer_std = malloc(count);
	buffer_ft = malloc(count);
	if (!buffer_std || !buffer_ft)
	{
		printf(RED "Malloc failed\n" RESET);
		update_unit_test_result(0);
		return ;
	}
	// Test functions
	file_fd = open(filename, O_RDONLY);
	ret1 = read(file_fd, buffer_std, count);
	close(file_fd);
	file_fd = open(filename, O_RDONLY);
	ret2 = ft_read(file_fd, buffer_ft, count);
	close(file_fd);
	
	#ifdef DEBUG
	printf("\nstd: read %d bytes\n", ret1);
	printf("ft_: read %d bytes\n", ret2);
	#endif
	// Compare results
	ret = ret1 == ret2 && !memcmp(buf, buffer_ft, count);
	printf("%s" RESET, (ret) ? GREEN "OK\n" : RED "KO\n");
	update_unit_test_result(ret);
	test_number++;
	// Clean up
	free(buffer_std);
	free(buffer_ft);
	close(file_fd);
	unlink(filename);
}

void test_read()
{
	printf(BLUE "*** READ vs. FT_READ ***\n" RESET);
	#ifdef DEBUG
	printf("DEBUG MODE: ON\n");
	#endif
	test("Hello, World!\n", 14);
	test("Hi", 1);
	test("Hi", 0); // 0 count
	test("a", 1); // Single character
	test("", 1); // Empty string
	test("                       ", 24); // White spaces
	test("!@#$%^&*()", 11);  // Special characters
    test("こんにちは", 16);  // Multibyte characters
	test("Hello\0World", 12); // Null character in the middle
    test("   Leading spaces", 18); // Leading spaces
    test("Trailing spaces   ", 19); // Trailing spaces
    test("Line1\nLine2\nLine3", 18); // Newline characters
    test("Tab\tSeparated\tValues", 21); // Tab characters
	char *src = create_random_string(100000000);
	test(src, 100000000);
	free(src);
}