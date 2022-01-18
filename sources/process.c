/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:58:48 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/18 18:39:34 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/pipex.h"

// void    ft_pipe_x_process(t_container *input, int i, int src_file_fd, int res_file_fd)
// {
// 	int		pipe_end[2];
// 	pid_t	res_pid;

// 	if (pipe(pipe_end) == FAIL)
// 		ft_perror_nl_free(input, "Error creating pipe");

// 	dup2(src_file_fd, STDIN_FILENO);
// 	close(src_file_fd);

// 	dup2(res_file_fd, STDOUT_FILENO);
// 	close(res_file_fd);

// 	res_pid = fork();
// 	if (res_pid == FAIL)
// 		ft_perror_nl_free(input, "Fork failure");

// 	if (res_pid == SUCCESS) // SUCCESS == 0;
// 	{
// 		close(pipe_end[read_fd]); // close 0
// 		execve(input->cmd[i].path, input->cmd[i].param, input->envp);
// 	}
// 	else
// 	{
// 		close(pipe_end[write_fd]); // close 1
// 		waitpid(res_pid, NULL, 0);
// 	}
// }

void    ft_prepare_x_process(t_container *input)
{
	int src_file_fd;
	int res_file_fd;
	int i;
	int pipe_end[2];
	pid_t res_pid;
	
	if (pipe(pipe_end) == FAIL)
		ft_perror_nl_free(input, "Error creating pipe");

	i = 1;
	
	res_pid = fork();
	if (res_pid == FAIL)
		ft_perror_nl_free(input, "Fork failure");

	if (res_pid == SUCCESS) // SUCCESS == 0; CHILD PROCESS
	{
		close(pipe_end[0]); // close 0 read_end

		src_file_fd = open(input->argv[0], O_RDONLY, 0777);
		if (src_file_fd == FAIL)
			ft_perror_nl_free(input, "Error reading source file");

		dup2(src_file_fd, STDIN_FILENO);
		dup2(pipe_end[1], STDOUT_FILENO);

		close(pipe_end[1]);

		execve(input->cmd[i].path, input->cmd[i].param, input->envp);
	}
	else // PARENT PROCESS
	{
		i = 2;
		waitpid(res_pid, NULL, 0);
		close(pipe_end[1]); // close 1 write_end

		res_file_fd = open(input->argv[input->argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (res_file_fd == FAIL)
			ft_perror_nl_free(input, "Error writing result file");

		dup2(pipe_end[0], STDIN_FILENO);
		dup2(res_file_fd, STDOUT_FILENO);

		close(pipe_end[0]);

		execve(input->cmd[i].path, input->cmd[i].param, input->envp);
	}
	// while (i < input->argc - 1)
	// {
	// 	ft_pipe_x_process(input, i, src_file_fd, res_file_fd);
	// 	i++;
	// }

	// FREE ALL SPLIT MALLOC HERE
	i = 1;
	while (i < input->argc - 1)
	{
		ft_free_table(input->cmd[i].param);
		free(input->cmd[i].path);
		i++;
	}
}