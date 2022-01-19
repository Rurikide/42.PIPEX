/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:03:11 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/18 22:19:34 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libft/libsources/libft.h"
# include "../libft/libsources/ft_printf.h"

typedef enum s_result
{
	SUCCESS = 0,
	FAIL = -1,
}	t_result;

typedef struct s_cmd
{
	char	*path;
	char	**param;
}	t_cmd;

typedef struct s_container
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**bins;
	t_cmd	*cmd;
}	t_container;

void		init_container(t_container *new, int ac, char **av, char **envp);
void		ft_parse_command_line(t_container *input);
char		*ft_find_path_variable(t_container *input);
t_result	ft_is_valid_command(t_container *input, int i, char *cmd);
void		ft_perror_nl_free(t_container *input, int i, char *message);
void		ft_perror_cmd_free(t_container *input, int i, char *message);
void		ft_prepare_x_process(t_container *input);
void		ft_pipe_x_process(t_container *input, int i, int i_fd, int o_fd);
void		free_container(t_container *input);

#endif
