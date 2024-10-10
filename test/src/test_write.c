/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:42:45 by tfregni           #+#    #+#             */
/*   Updated: 2024/10/10 16:25:06 by tfregni          ###   ########.fr       */
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
		printf(RED "Dup failed\n" RESET);
		return(0);
	}
	int ret = dup2(pipe_fd[1], fd);	
	if (ret < 0)
	{
		printf(RED "dup2 failed\n" RESET);
		return (0);
	}
	close(pipe_fd[1]);
	return (ret);
}

static void	test(int fd, const void *buf, size_t count)
{
	static int	test_number = 1;
	int ret;
	int ret1, ret2;
	int saved_fd;
	
	printf("Test %d: ", test_number);
	if (!create_pipe() || !redirect_stdout(&saved_fd, fd))
	{
		update_unit_test_result(0);
		return ;
	}
	
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
	ret1 = write(fd, buf, count);
	read(pipe_fd[0], buffer_std, count);
	ret2 = ft_write(fd, buf, count);
	read(pipe_fd[0], buffer_ft, count);
	// End of reading
	close(pipe_fd[0]);
	// Restore original fd
	dup2(saved_fd, fd);
	
	#ifdef DEBUG
	write(1, "Output std: ", 12);
	write(1, buffer_std, count);
	write(1, "Output ft: ", 11);
	write(1, buffer_ft, count);
	#endif
	// Compare results
	ret = ret1 == ret2 && !memcmp(buffer_std, buffer_ft, count);
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
	test(1, "Hello, World!\n", 14);
	test(1, "", 1);
	test(1, "Hi", 1);
	test(1, "Hi", 0);
	char *src = create_random_printable_string(8192);
	test(1, src, 100);
	free(src);
	test(56, "Hi", 2);
}