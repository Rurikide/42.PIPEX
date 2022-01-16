/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:32:40 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/16 13:07:31 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_perror_nl_free(t_container *unix, char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	// ft_free_table(unix->bins);
	free(unix->cmd);
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

char *ft_find_path_variable(t_container *unix)
{
	if (unix->envp == NULL)
		return (NULL);
	while (unix->envp != NULL)
	{
		if (ft_strncmp(*unix->envp, "PATH=", 5) == SUCCESS)
			return (&(*unix->envp)[6]);
		else
			unix->envp++;
	}
	return (NULL);
}

t_result	ft_is_valid_command(t_container *unix, size_t i, char *cmd)
{
	// char **paths;
	char *test_road;
	size_t nb;
	
	// paths = ft_split(ft_find_path_variable(unix), ':');
	nb = 0;
	while (unix->bins[nb] != NULL)
	{
		test_road = ft_strjoin_symbol(unix->bins[nb], '/', cmd);
		// Vérification à faire?
		if (access(test_road, F_OK) == SUCCESS)
		{
			ft_printf("THE CORRECT PATH IS %s and path number is %d\n", test_road, nb);
			unix->cmd[i].path = test_road;
			free(test_road);
			return (SUCCESS);
		}
		free(test_road);
		test_road = NULL;
		nb++;
	}
	return (FAIL);
}

void ft_parse_command_line(t_container *unix)
{
	size_t	i;
	
	i = 1;
	unix->bins = ft_split(ft_find_path_variable(unix), ':');
	// Vérification à faire?
	while (unix->argv[i] != NULL && unix->argv[i + 1] != NULL)
	{
		ft_printf("checking cmd #%d\n", i);
		unix->cmd[i].param = ft_split(unix->argv[i], ' ');
		if (unix->cmd[i].param == NULL)
		{
			ft_perror_nl_free(unix, "Error parse cmd");
		}
		if (ft_is_valid_command(unix, i, unix->cmd[i].param[0]) == FAIL)
		{
			ft_perror_nl_free(unix, "cmd is invalid");
		}
		i++;
	}
	
	// ft_free_table(unix->bins);
}

void init_container(t_container *new, int argc, char **argv, char **envp)
{
	new->argc = argc;
	new->argv = argv;
	new->envp = envp;

	new->cmd = (t_cmd *)ft_calloc(argc - 2, sizeof(t_cmd));
	if (!new->cmd)
	{
		// DOIS-JE FREE NEW->CMD???
		ft_perror_nl_free(new, "Error malloc");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_container	unix;

	if (argc == 5)
	{
		init_container(&unix, argc - 1, &argv[1], envp);
		ft_parse_command_line(&unix);
		// ft_prepare_x_process(&unix);
		// ft_free_table(unix.bins);
		free(unix.cmd);
	}
	else
	{
		ft_printf("Incorrect input. Please enter : file1 cmd1 cmd2 file2");
	}
	return (0);
}