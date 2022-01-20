/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:58:48 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/19 20:57:42 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_perror_nl_free(t_container *input, int i, char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	while (i >= 1)
	{
		ft_free_table(input->cmd[i].param);
		free(input->cmd[i].path);
		i--;
	}
	ft_free_table(input->bins);
	free(input->cmd);
	exit(EXIT_FAILURE);
}

void	ft_perror_cmd_free(t_container *input, int i, char *message)
{
	int	j;

	j = 1;
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	while (j <= i)
	{
		ft_free_table(input->cmd[j].param);
		if (j < i)
			free(input->cmd[j].path);
		j++;
	}
	ft_free_table(input->bins);
	free(input->cmd);
	exit(EXIT_FAILURE);
}

void	free_container(t_container *input)
{
	int	i;

	i = 1;
	while (i < input->argc - 1)
	{
		ft_free_table(input->cmd[i].param);
		free(input->cmd[i].path);
		i++;
	}
	ft_free_table(input->bins);
	free(input->cmd);
}

void	ft_pipe_x_process(t_container *input, int i, int i_fd, int o_fd)
{
	int		pipe_end[2];
	pid_t	res_pid;

	if (pipe(pipe_end) == FAIL)
		ft_perror_nl_free(input, input->argc - 2, "Error creating pipe");
	dup2(i_fd, 0);
	close(i_fd);
	if (i == input->argc - 2)
		dup2(o_fd, 1);
	else
		dup2(pipe_end[1], 1);
	res_pid = fork();
	if (res_pid == FAIL)
		ft_perror_nl_free(input, input->argc - 2, "Fork failure");
	if (res_pid == SUCCESS)
		execve(input->cmd[i].path, input->cmd[i].param, input->envp);
	else
	{
		close(pipe_end[1]);
		waitpid(res_pid, NULL, 0);
	}
	if (i < input->argc - 2)
		return (ft_pipe_x_process(input, i + 1, pipe_end[0], o_fd));
}

void	ft_prepare_x_process(t_container *input)
{
	int	i_fd;
	int	o_fd;
	int	i;

	if (ft_strdouble(input->argv[0], input->argv[input->argc - 1]) == true)
		ft_perror_nl_free(input, input->argc - 2, "Files must be different");
	o_fd = open(input->argv[input->argc - 1], \
		O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (o_fd == FAIL)
		ft_perror_nl_free(input, input->argc - 2, "Error writing result file");
	i_fd = open(input->argv[0], O_RDONLY, 0777);
	if (i_fd == FAIL)
		ft_perror_nl_free(input, input->argc - 2, "Error reading source file");
	i = 1;
	ft_pipe_x_process(input, i, i_fd, o_fd);
}
