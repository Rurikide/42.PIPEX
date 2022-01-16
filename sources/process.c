/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:58:48 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/16 13:04:12 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/pipex.h"

void    ft_pipe_x_process(t_container *unix, int nb, int src_file_fd, int res_file_fd)
{
	int		*end[2];
	pid_t	res_pid;

	if (pipe(end) == FAIL)
		ft_perror_nl_free(unix, "Error creating pipe");

	res_pid = fork();
	if (res_pid == FAIL)
		ft_perror_nl_free(unix, "Fork failure");


	dup2(src_file_fd, STDIN_FILENO); //0
	close(src_file_fd);

	dup2(res_file_fd, STDOUT_FILENO); //1
	close(res_file_fd);

	if (res_pid == SUCCESS) // SUCCESS == 0;
	{
		close(end[read_fd]); // close 0

		dup2(end[write_fd], STDOUT_FILENO); // redirecting STDOUT 1 to pipe[1]

		execve(unix->cmd[nb].path, unix->cmd[nb].param, unix->envp);
	}
	else
	{
		close(end[write_fd]); // close 1
		
		dup2(end[read_fd], STDIN_FILENO); // redirecting STDOUT 0 to pipe[0]
		
		waitpid(res_pid, NULL, 0);
	}
	
}

void    ft_prepare_x_process(t_container *unix)
{
	int src_file_fd;
	int res_file_fd;
	int nb;

	src_file_fd = open(unix->argv[0], O_RDONLY, 0777);
	if (src_file_fd == FAIL)
		ft_perror_nl_free(unix, "Error reading source file");
	res_file_fd = open(unix->argv[unix->argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (res_file_fd == FAIL)
		ft_perror_nl_free(unix, "Error writing result file");
	
	nb = 1;
	while (nb < unix->argc - 1)
	{
		ft_pipe_x_process(unix, nb, src_file_fd, res_file_fd);
		nb++;
	}
	
	// close(src_file_fd);
	// close(res_file_fd);
}