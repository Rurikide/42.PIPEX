/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:03:11 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/16 13:04:45 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libft/libsources/libft.h"
# include "../libft/libsources/ft_printf.h"

enum s_pipe
{
	read_fd = 0,
	write_fd = 1,
} t_pipe;

typedef enum s_result
{
	SUCCESS = 0,
	FAIL = -1,
} t_result;

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

void		init_container(t_container *new, int argc, char **argv, char **envp);
void		ft_parse_command_line(t_container *unix);
char		*ft_find_path_variable(t_container *unix);
t_result	ft_is_valid_command(t_container *unix, size_t i, char *cmd);
char		*ft_strjoin_symbol(char *str1, char symbol, char *str2);
void		ft_perror_nl_free(t_container *unix, char *message);
void		ft_prepare_x_process(t_container *unix);
void		ft_pipe_x_process(t_container *unix, int nb, int src_file_fd, int res_file_fd);

#endif
