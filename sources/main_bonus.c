/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:32:40 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/19 18:28:21 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

t_result	ft_is_valid_command(t_container *input, int i, char *cmd)
{
	size_t	nb;

	nb = 0;
	while (input->bins[nb] != NULL)
	{
		input->cmd[i].path = ft_strjoin_symbol(input->bins[nb], '/', cmd);
		if (access(input->cmd[i].path, F_OK) == SUCCESS)
			return (SUCCESS);
		free(input->cmd[i].path);
		nb++;
	}
	return (FAIL);
}

void	ft_parse_command_line(t_container *input)
{
	int	i;

	i = 1;
	input->bins = ft_split(ft_find_path_variable(input), ':');
	if (input->bins == NULL)
	{
		ft_printf("Error path variable is NULL\n");
		ft_free_table(input->bins);
		free(input->cmd);
		exit(EXIT_FAILURE);
	}
	while (input->argv[i] && input->argv[i + 1])
	{
		input->cmd[i].param = ft_split(input->argv[i], ' ');
		if (input->cmd[i].param == NULL)
			ft_perror_cmd_free(input, i, "Error split cmd");
		if (ft_is_valid_command(input, i, input->cmd[i].param[0]) == FAIL)
		{
			ft_printf("cmd #%d is invalid.\n", i);
			ft_perror_cmd_free(input, i, "Error parse cmd");
		}
		i++;
	}
}

char	*ft_find_path_variable(t_container *input)
{
	if (input->envp == NULL)
		return (NULL);
	while (input->envp != NULL)
	{
		if (ft_strncmp(*input->envp, "PATH=", 5) == SUCCESS)
			return (&(*input->envp)[6]);
		else
			input->envp++;
	}
	return (NULL);
}

void	init_container(t_container *new, int ac, char **av, char **envp)
{
	if (envp == NULL)
	{
		ft_printf("Error envp is NULL\n");
		exit (EXIT_FAILURE);
	}
	new->argc = ac;
	new->argv = av;
	new->envp = envp;
	new->bins = NULL;
	new->cmd = malloc(sizeof(t_cmd) * (ac - 1));
}

int	main(int argc, char **argv, char **envp)
{
	t_container	input;

	if (argc >= 5)
	{
		init_container(&input, argc - 1, &argv[1], envp);
		ft_parse_command_line(&input);
		ft_prepare_x_process(&input);
		free_container(&input);
	}
	else
	{
		ft_printf("Incorrect input. Please enter : file1 cmd1 cmd2 file2\n");
	}
	return (0);
}
