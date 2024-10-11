/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:42:45 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/11 12:57:05 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test_libasm.h>

int pipe_fd[2];

static int create_pipe()
{
	if (pipe(pipe_fd) < 0)
	{
		printf(RED "Pipe failed\n" RESET);
		return(0);
	}
	return (1);
}

static int redirect_stdout(int *saved_fd, int fd)
{	
	*saved_fd = dup(fd);
	if (*saved_fd < 0)
	{
		#ifdef DEBUG
		printf(RED "Dup failed\n" RESET);
		#endif
		return(0);
	}
	int ret = dup2(pipe_fd[1], fd);	
	if (ret < 0)
	{
		#ifdef DEBUG
		printf(RED "dup2 failed\n" RESET);
		#endif
		close(pipe_fd[0]);
        close(pipe_fd[1]);
		close(*saved_fd);
		return (0);
	}
	close(pipe_fd[1]);
	return (ret);
}
void test_failure(int *test_number, int fd, const void *buf, size_t count)
{
	ssize_t ret;
	ssize_t ret_std, ret_ft;
	int err_std, err_ft;
	
	printf(RED "FAILURE TEST: " RESET);
	ret_std = write(fd, buf, count);
	if (ret_std < 0)
		err_std = errno;
	ret_ft = ft_write(fd, buf, count);
	if (ret_ft < 0)
		err_ft = errno;
	#ifdef DEBUG
	if (ret_std < 0 || ret_ft < 0)
	{
		printf("Std: ret: %zd, error: %s\n", ret_std, strerror(err_std));
		printf("Std: ret: %zd, error: %s\n", ret_ft, strerror(err_ft));
	}
	#endif
	ret = (ret_std == ret_ft) && (err_std == err_ft);
	printf("%s" RESET, (ret) ? GREEN "OK\n" : RED "KO\n");
	update_unit_test_result(ret);
	*test_number += 1;
}
int restore_fd(int saved_fd, int fd)
{
	if (dup2(saved_fd, fd) < 0)
	{
		printf(RED "dup2 restore failed\n" RESET);
		return (0);
	}
	return (1);
}

static void	test(int fd, const void *buf, size_t count)
{
	static int	test_number = 1;
	int ret;
	int ret1, ret2;
	int saved_fd;
	char *buffer_std, *buffer_ft;
	
	printf("Test %d: ", test_number);
	if (!buf || !create_pipe() || !redirect_stdout(&saved_fd, fd))
	{
		test_failure(&test_number, fd, buf, count);
		return ;
	}
	
	// Init buffers
	buffer_std = malloc(count);
	buffer_ft = malloc(count);
	if (!buffer_std || !buffer_ft)
	{
		if (!restore_fd(saved_fd, fd))
			return ;
		printf(RED "Malloc failed\n" RESET);
		test_number++;
		return ;
	}
	// Test functions
	ret1 = write(fd, buf, count);
	read(pipe_fd[0], buffer_std, count);
	ret2 = ft_write(fd, buf, count);
	read(pipe_fd[0], buffer_ft, count);
	// End of reading
	close(pipe_fd[0]);
	// Restore original fd
	if (!restore_fd(saved_fd, fd))
		return ;
	
	#ifdef DEBUG
	write(1, "Output std: ", 12);
	write(1, buffer_std, count);
	write(1, "\n", 1);
	write(1, "Output ft: ", 11);
	write(1, buffer_ft, count);
	write(1, "\n", 1);
	#endif
	// Compare results
	if (ret1 < 0 || ret2 < 0)
	{
		printf(RED "Error after setup: " RESET);
		test_failure(&test_number, fd, buf, count);
		free(buffer_std);
		free(buffer_ft);
		close(saved_fd);
		return ;
	}	
	ret = (ret1 == ret2) && (!memcmp(buffer_std, buffer_ft, count));
	printf("%s" RESET, (ret) ? GREEN "OK\n" : RED "KO\n");
	update_unit_test_result(ret);
	test_number++;
	// Clean up
	free(buffer_std);
	free(buffer_ft);
	close(saved_fd);
}

void test_write()
{
	printf(BLUE "*** WRITE vs. FT_WRITE ***\n" RESET);
	#ifdef DEBUG
	printf("DEBUG MODE: ON\n");
	#endif
	// Base tests
	for (int i = 0; g_base_test_strings[i]; i++)
		test(1, g_base_test_strings[i], strlen(g_base_test_strings[i]));
	// Extra tests
	test(1, "Hi", 1);
	test(1, "Hi", 0); // 0 count
	test(1, "", 1); // Empty string nonzero count
    test(1, "こんにちは", 4);  // Multibyte characters different count
	test(1, "Hello\0World", 12); // Null character in the middle
	char *src = create_random_printable_string(8192);
	test(1, src, 100);
	free(src);
	// Failure tests
	test(56, "Hello, World!\n", 14);
	test(1, "Hello, World!\n", -1);
	test(1, NULL, 14);
}