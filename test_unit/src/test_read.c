/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:42:45 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/11 15:50:06 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test_libasm.h>

static void	test(const void *buf, size_t count)
{
	static int	test_number = 1;
	int ret;
	ssize_t ret1, ret2;
	int err_std, err_ft;
	char *filename = ".test_read";
	
	printf("Test %d: ", test_number);
	int file_fd = open(filename, O_CREAT | O_WRONLY, 0644);
	if (file_fd < 0 || write(file_fd, buf, count) < 0)
	{
		printf(RED "File creation failed\n" RESET);
		test_number++;
		close(file_fd);
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
		test_number++;
		return ;
	}
	// Test functions
	file_fd = open(filename, O_RDONLY);
	ret1 = read(file_fd, buffer_std, count);
	if (ret1 < 0)
		err_std = errno;
	close(file_fd);
	file_fd = open(filename, O_RDONLY);
	ret2 = ft_read(file_fd, buffer_ft, count);
	if (ret2 < 0)
		err_ft = errno;
	close(file_fd);
	
	#ifdef DEBUG
	printf("\nstd: read %zd bytes\n", ret1);
	printf("ft_: read %zd bytes\n", ret2);
	#endif
	// Compare results
	ret = ret1 == ret2;
	if (ret1 < 0 || ret2 < 0)
	{
		printf(RED "FAILURE TEST: " RESET);
		#ifdef DEBUG
		printf("\nstd: error %d - %s\n", err_std, strerror(err_std));
		printf("ft_: error %d - %s\n", err_ft, strerror(err_ft));
		#endif
		ret = ret && (err_std == err_ft);
	}
	else
		ret = ret && (!memcmp(buf, buffer_ft, count));
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
	// int max_size = 4096;
	// Base tests
	// for (int i = 0; g_base_test_strings[i]; i++)
	// 	test(g_base_test_strings[i], strlen(g_base_test_strings[i]));
	// // Extra tests
	// test("Hi", 0); // 0 count
	// test("a", 1); // Single character
	// test("", 1); // Empty string nonzero count
    // test("こんにちは", 5);  // Multibyte characters different count
	// test("Hello\0World", 12); // Null character in the middle
	// char *src = create_random_string(max_size);
	// test(src, max_size);
	// free(src);
	// // Failure test
	test(NULL, 1);
	test("Hello", 0);
	test("Hello", -1);
	test("Hello", 56);
}