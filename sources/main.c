/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:32:40 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/16 20:00:49 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_perror_nl_free(t_container *input, char *message)
{
	int i;

	i = 1;
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	while (i < input->argc - 1)
	{
		ft_free_table(input->cmd[i].param);
		free(input->cmd[i].path);
		i++;
	}
	free(input->cmd);
	exit(EXIT_FAILURE);
}


char	*ft_strjoin_symbol(char *str1, char symbol, char *str2)
{
	char *new_str;
	int	bytes;
	int	i;

	i = 0;
	bytes = ft_strlen(str1) + ft_strlen(str2) + 2;
	new_str = malloc(sizeof(char) * bytes);
	
	while(str1 != NULL && *str1)
	{
		new_str[i++] = *(str1++);
	}
	new_str[i++] = symbol;
	while (str2 != NULL && *str2)
	{
		new_str[i++] = *(str2++);
	}
	new_str[i] = '\0';
	return (new_str); 
}

t_result	ft_is_valid_command(t_container *input, int i, char *cmd)
{
	size_t nb;
	
	nb = 0;
	while (input->bins[nb] != NULL)
	{
		input->cmd[i].path = ft_strjoin_symbol(input->bins[nb], '/', cmd);
		// Vérification à faire?
		if (access(input->cmd[i].path, F_OK) == SUCCESS)
		{
			ft_printf("THE CORRECT PATH IS %s and path number is %d\n", input->cmd[i].path, nb);
			return (SUCCESS);
		}
		free(input->cmd[i].path);
		nb++;
	}
	return (FAIL);
}

void ft_parse_command_line(t_container *input)
{
	int	i;
	
	i = 1;
	input->bins = ft_split(ft_find_path_variable(input), ':');
	// Vérification à faire?
	while (input->argv[i] && input->argv[i + 1])
	{
		ft_printf("checking cmd #%d\n", i);
		input->cmd[i].param = ft_split(input->argv[i], ' ');
		// Vérification à faire?
		if (input->cmd[i].param == NULL)
		{
			ft_perror_nl_free(input, "Error parse cmd");
		}
		if (ft_is_valid_command(input, i, input->cmd[i].param[0]) == FAIL)
		{
			ft_perror_nl_free(input, "cmd is invalid");
		}
		i++;
	}
	ft_free_table(input->bins);
}

char *ft_find_path_variable(t_container *input)
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

void init_container(t_container *new, int argc, char **argv, char **envp)
{
	new->argc = argc;
	new->argv = argv;
	new->envp = envp;
	new->bins = NULL;

	new->cmd =  malloc(sizeof(t_cmd) * (argc - 1));
	// if (!new->cmd)
	// {
	// 	// DOIS-JE FREE NEW->CMD???
	// 	ft_perror_nl_free(new, "Error malloc");
	// }
}

int	main(int argc, char **argv, char **envp)
{
	t_container	input;
	
	if (argc == 5)
	{
		init_container(&input, argc - 1, &argv[1], envp);
		ft_parse_command_line(&input);
		ft_prepare_x_process(&input);
		free(input.cmd);
	}
	else
	{
		ft_printf("Incorrect input. Please enter : file1 cmd1 cmd2 file2");
	}
	return (0);
}