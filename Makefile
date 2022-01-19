# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/01 22:25:32 by tshimoda          #+#    #+#              #
#    Updated: 2022/01/18 20:58:10 by tshimoda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= pipex

AR= ar rc
RM= rm -rf

CC= gcc
CFLAGS= -Wall -Werror -Wextra -c

SDIR= sources
ODIR= objects

SRCS= main.c \
		process.c \


OBJS= $(SRCS:.c=.o)

SFIX= $(addprefix $(SDIR)/, $(SRCS))
OFIX= $(addprefix $(ODIR)/, $(OBJS))

VPATH= $(SDIR)

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(NAME): $(ODIR) $(OFIX)
	$(MAKE) -C ./libft
	$(CC) $(OFIX) -lft -L./libft -o $(NAME)
	@echo "\033[1;32m 下田、徳太郎のPIPEX\033[0;39m"

all:    $(NAME)

$(ODIR):
		mkdir -p $(ODIR)


clean:
	$(MAKE) clean -C ./libft
	$(RM) $(ODIR)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
	@echo "\033[1;34m make fclean done!\033[0;39m"

re:     clean all

.PHONY: all clean flcean re